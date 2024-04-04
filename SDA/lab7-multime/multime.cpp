#include "multime.h"
#include "iterator.h"
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


/// constructor multime
/// Complexitate timp : θ(1)
/// 
Multime::Multime() {
	rad = -1;
	dimensiune = 0;
	primLiber = 0;
	cp = 4;
	arbore = new Nod[cp];
	for (int i = 0; i < cp - 1; i++) {
		arbore[i].st = i + 1;
	}
	arbore[cp - 1].st = -1;
}



/// redimensioneaza arborele
/// Complexitate timp : θ(n)
/// 
void Multime::redim() {
	Nod* arboreNou = new Nod[cp * 2];
	for (int i = 0; i < cp; i++) {
		arboreNou[i].e = arbore[i].e;
		arboreNou[i].st = arbore[i].st;
		arboreNou[i].dr = arbore[i].dr;
	}
	delete[] arbore;
	arbore = arboreNou;
	primLiber = cp;
	for(int i= cp; i < cp * 2 ; i++) {
		arbore[i].st = i + 1;
	}
	arbore[cp*2-1].st = -1;
	cp *= 2;
}

/// gaseste minimul din arbore
/// Comlexitate timp:
/// caz favorabil: θ(1) daca radacina este min
/// caz defavorabil: θ(n) daca minimul este ultimul nod si toate el din noduri sunt strict crescatoare
/// caz mediu: O(n)
/// 
TElem Multime::minim(int rad) const {
	if (rad == -1) {
		return NULL_TELEM;
	}
	else {
		int radNou = rad;
		while (arbore[radNou].st != -1) {
			radNou = arbore[radNou].st;
		}
		return arbore[radNou].e;
	}
}

/// gaseste maximul din arbore
/// Comlexitate timp:
/// caz favorabil: θ(1) daca radacina este max
/// caz defavorabil: θ(n) daca maximul este ultimul nod si toate el din noduri sunt strict descrescatoare
/// caz mediu: O(n)
/// 
TElem Multime::maxim(int rad) const {
	if (rad == -1) {
		return NULL_TELEM;
	}
	else {
		int radNou = rad;
		while (arbore[radNou].dr != -1) {
			radNou = arbore[radNou].dr;
		}
		return arbore[radNou].e;
	}
}

/*Adauga un element nou in multime
* Daca elementul exista deja in multime returneaza false
*
* Complexitate timp:
*	caz favorabil:O(n) trebuie cautat el. in arbore
*	caz mediu: O(n)
*	caz defavorabil: θ(n) este minimul sau maximul din multime astfel trebuie parcurs tot arborele si toate el din noduri sunt strict crescatoare/descrescatoare
*
*/
bool Multime::adauga(TElem elem) {
	if (cauta(elem) == true) return false;
	if (primLiber >= cp-1) {

		redim(); 
		
	}
	int golNou = arbore[primLiber].st;
	arbore[primLiber].e = elem;
	arbore[primLiber].st = -1;
	arbore[primLiber].dr = -1;
	int current = rad;
	int parinte = -1;
	while (current != -1) {
		parinte = current;
		if (rel(elem, arbore[current].e) == true) {
			current = arbore[current].st;
		}
		else {
			current = arbore[current].dr;
		}
	}
	if (rad == -1) { 
		rad = primLiber;
	}
	else if (rel(elem, arbore[parinte].e)) {
		arbore[parinte].st = primLiber;
	}
	else {
		arbore[parinte].dr = primLiber;
	}
	primLiber = golNou;
	
	dimensiune += 1;
	return true;
}


/// functie de stergere recursiva
/// Complexitate timp
/// caz favorabil: θ(1) daca elementul este radacina
/// caz defavorabil: θ(n) daca elementul este ultimul nod si trebuie parcurs tot arborele cand toate elementele sunt strict crescatoare/descrescatoare
/// caz mediu: O(n)
/// 
int Multime::stergeRec(int nod,TElem e, bool& sters)//theta(O(n)) < n is the number of pairs
{
	if (nod == -1) {
		return nod;
	}
	if (e == arbore[nod].e) {
		sters = true;
		if (arbore[nod].st == -1) {
			int drDes = arbore[nod].dr;
			arbore[nod].e = NULL_TELEM;
			arbore[nod].dr = -1;
			arbore[nod].st = -1;
			return drDes;
		}
		else if (arbore[nod].dr == -1) {
			int stChild = arbore[nod].st;
			arbore[nod].e = NULL_TELEM;
			arbore[nod].dr = -1;
			arbore[nod].st = -1;
			return stChild;
		}
		else {
			int maxN = maxim(arbore[nod].st);
			arbore[nod].e = arbore[maxN].e;
			arbore[nod].st = stergeRec(arbore[nod].st, arbore[maxN].e, sters);
		}
	}
	else if (rel(e, arbore[nod].e)) {
		arbore[nod].st = stergeRec(arbore[nod].st, e, sters);
	}
	else {
		arbore[nod].dr = stergeRec(arbore[nod].dr, e, sters);
	}
	return nod;
}


/*Sterge element din multime
* Daca el. nu se afla in multime returneaza false
*
* Complexitate timp:
*		caz favorabil:θ(1) daca el. de sters este radacina
*		caz mediu:O(n);
*		caz defavorabil: θ(n) daca elementul este ultimul nod si trebuie parcurs tot arborele cand toate elementele sunt strict crescatoare/descrescatoare
*                        adica toate el. sunt mai mici sau mai mari decat parintele
*
*/
bool Multime::sterge(TElem elem) {
	if (cauta(elem) == false) {
		return false;
	}
	if (dimensiune == 0) {
		return false;
	}
	bool sters = false;
	rad = stergeRec(rad, elem, sters);
	if (sters) {
		dimensiune -= 1;
	}
	return sters;
}

/*Cauta un element
* Daca el. se afla in multime returneaza true, false in caz contrar
*
* Complexitate timp:
*		caz favorabil:θ(1) daca el. este radacina
*		caz defavorabil:θ(n) daca el. este ultimul nod si trebuie parcurs tot arborele cand toate elementele sunt strict crescatoare/descrescatoare
*		caz mediu:O(n) 
*/
bool Multime::cauta(TElem elem) const {
	if (dimensiune == 0) {
		return false;
	}
	else {
		int radu = rad;
		while (radu != -1) {
			if (arbore[radu].e == elem) {
				return true;
			}
			else if (rel(elem, arbore[radu].e)) {
				radu = arbore[radu].st;
			}
			else {
				radu = arbore[radu].dr;
			}
		}
		return false;
	}

}

/// returneaza diferenta dintre maxim si minim
/// daca multimea este vida returneaza -1
/// Complexitate timp
/// caz favorabil: θ(1) daca exista doar un element in multime
/// caz defavorabil: θ(n) daca minimul si maximul sunt ultimele noduri
/// caz mediu: O(n)
/// 
/// subalgoritm diferentaMaxMin(){
///		daca multimea este vida atunci returneaza -1
///     max <- maxim(rad);
///     min <- minim(rad);
///     returneaza max - min;
/// }
/// 
/// 
int Multime::diferențaMaxMin() const {
	if (dimensiune == 0) {
		return -1;
	}
	int max = maxim(rad);
	int min = minim(rad);
	return max - min;
}

/*Returneaza numarul de el. din multime
* Complexitate timp:
*		O(1)
*/
int Multime::dim() const {

	return dimensiune;
}


/*
* Verifica daca multimea este vida
* returneaza true daca multimea este vida
* false in caz contrar
* Complexitate timp:
*		O(1)
*/
bool Multime::vida() const {

	if (dimensiune != 0) return false;
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

	delete[] arbore;
	
}
