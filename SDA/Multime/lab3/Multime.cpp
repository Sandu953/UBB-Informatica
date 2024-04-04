#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>
#include <new>

using namespace std;

//returneaza true daca e1 <= e2, false in caz contrar
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Nod::Nod(TElem e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

//returneaza valoarea elementuli din nodul respectiv
TElem Nod::element() {
	return e;
}

//returneaza adresa urmatorului nod
PNod Nod::urmator() {
	return urm;
}

Multime::Multime() {
	this->prim = nullptr;
	this->n = 0;
}


/*Adauga un element nou in multime 
* Daca multimea este goala adaugam la inceput
* Daca elementul exista deja in multime returneaza false
* 
* Complexitate timp:
*	caz favorabil:θ(1) daca multimea este vida
*	caz mediu: O(n)
*	caz defavorabil: θ(n) elementul trebuie adaugat la final
*					 se va parcurge multimea de doua ori pentru 
*					 adaugare si inca o data pt. cautarea el. 
*					 adica T(3*n) care apartine de θ(n)
* 
*/
bool Multime::adauga(TElem elem) {
	//cand multimea este vida
	if (this->n == 0) {
		PNod q = new Nod(elem, nullptr);
		q->urm = prim;
		prim = q;
		this->n += 1;
		return true;
	}
	//cauta el. in multime
	else if (cauta(elem) == false) {
		PNod q = new Nod(elem, nullptr);
		this->n += 1;
		IteratorMultime i = iterator();
		//verific daca el. trebuie pus pe prima poz.
		if (rel(i.element(), elem) == false) {
			q->urm = i.curent;
			prim = q;
			return true;
		}

		PNod el = i.curent;
		int ok = 0;
		while (i.valid()) {	
			if (rel(i.element(), elem) == false) {
				q->urm = i.curent;//creaza legatura dintre el. de adaugat si urmatorul el. mai mare din multime
				ok = 1;
				break;
			}
			el = i.curent;
			i.urmator();
		}
		i.prim();
		while (i.valid()) {
			if (i.element() == el->e) {
				i.curent->urm = q;//creaza legatura dintre el. de adaugat si urmatorul el. mai mic din multime
				break;
			}
			if (i.curent->urm == nullptr) break;
			i.urmator();
		}
		//daca el. trebuie adaugat la finalul multimii
		if (ok == 0) {
			i.curent->urm = q;
		}
		return true;
	}
	return false;
}



/*
* Adauga elementele din b in a
* daca un el. din b care exista deja in a
* acesta nu va fi adaugat
* 
* Pseudocod:
*	subalgoritm reuniune( Mulime b )
*		Iterator i = @iterator
*		cat timp(i.valid) executa
*			@adauga i.element
*			i.urmator
*		Sf. cat timp
*	Sf. subalgoritm
* 
* Complexitate timp:
*		T(n*m + (m(m-1)/2) + m)
*		n-dimensiunea lui a
*		m-dimensiunea lui b
*		trebuie sa parcurg multimea a de m ori(pentru a face adaugarea),
*       dar de fiecare data a-ul se mareste cu 1
*       pana a ajunge la dimensiunea de n+m
*		si trebuie parcursa si multimea b 
*		caz favorabil = O(m^2)
		caz defavorabil = O(max(m*n,6^2))
		caz mediu = O(m^2)
* 
*/
void Multime::reuniune(const Multime& b) {
	IteratorMultime i = b.iterator();
	while (i.valid()) {
		adauga(i.element());
		i.urmator();
	}
}

/*Sterge element din multime
* Daca el. nu se afla in multime returneaza false
* 
* Complexitate timp:
*		caz favorabil:θ(1) daca el. de sters se afla pe prima pozitie
*		caz mediu:θ(n) el se afla undeva in mijlocul multimii
*		caz defavorabil:O(n) el nu se afla in multime
* 
*/
bool Multime::sterge(TElem elem) {

	IteratorMultime i = iterator();
	
	//daca el. nu exista returneaza false
	if (cauta(elem) == false)return false;
	
	//daca el. se afla pe prima pozitie
	if (i.element() == elem) {
		PNod p = prim;
		this->prim = prim->urm;
		delete p;
		this->n -= 1;
		return true;
		
	}

	//vecinii el. de sters, trebuie creeata legatura intre ei
	PNod el = i.curent;
	PNod el2 = i.curent;
	
	int ok = 0;

	while (i.valid()) {
		el = i.curent;
		if (i.element() == elem) {
			if (i.curent->urm == nullptr) {
				ok = 1;//daca el. se afla pe ultima pozitie
				break;
			}
			i.urmator();
			el = i.curent;
			break;
		}
		el2 = i.curent;
		i.urmator();
	}
	if (ok == 1) {
		i.prim();
		while (i.valid()) {

			if (i.element() == el2->e) {
				i.curent->urm = nullptr;
				delete i.curent->urm;
				this->n -= 1;//daca el. se afla pe ultima pozitie sterg el. si modific urm. la el. antrior la nullptr
				return true;
			}
			i.urmator();
		}

	}

	i.prim();
	
	while (i.valid()) {

		if (i.element() == el2->e) {
			i.curent->urm = el;//creez legatura dintre vecinii el. de sters
			this->n -= 1;
			return true;
		}
		i.urmator();
	}

	return false;
}


/*Cauta un element
* Daca el. se afla in multime returneaza true, false in caz contrar
* 
* Complexitate timp:
*		caz favorabil:θ(1) daca el. se afla pe prima pozitie
*		caz mediu:θ(n) daca el. se afla in interiorul multimii
*		caz defavorabil:O(n)el. nu se afla in multime;
*/
bool Multime::cauta(TElem elem) const {

	IteratorMultime i = iterator();
	//parcurgem multimea
	while (i.valid()) {
		//daca il gasim returneaza true 
		if (elem == i.element()) {
			return true;
		}
		i.urmator();
	}
	return false;
}

/*Returneaza numarul de el. din multime
* Complexitate timp:
*		O(1)
*/
int Multime::dim() const {

	return n;
}


/*
* Verifica daca multimea este vida
* returneaza true daca multimea este vida
* false in caz contrar
* Complexitate timp:
*		O(1)
*/
bool Multime::vida() const {

	if (n != 0) return false;
	return true;
}

/*Returneaza un iterator pe multime
* 
*  Complexitate timp:
*		O(1)
*/
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

/*Destructorul multimii
* Complexitate timp:
*		caz favorabil = caz mediu = caz defavorabil = O(n)
*/
Multime::~Multime() {

	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}
