#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <new>

using namespace std;


// functie de redimensionare a MD-ului
// Complexitate de timp: θ(n)
//
void MD::redim() {
	Nod* nodNou = new Nod[this->ldi.cp * 2];
	for (int i = 0;i < this->ldi.cp;i++) {
		nodNou[i] = this->ldi.noduri[i];
	}

	for (int i = this->ldi.cp;i < 2 * this->ldi.cp - 1;i++) {
		nodNou[i].urm = i + 1;
	}
	nodNou[this->ldi.cp * 2 - 1].urm = -1;

	for (int i = this->ldi.cp + 1;i < 2 * this->ldi.cp;i++) {
		nodNou[i].prec = i - 1;
	}
	nodNou[this->ldi.cp].prec = -1;

	this->ldi.primGol = this->ldi.cp;
	this->ldi.cp = this->ldi.cp * 2;

	delete[] this->ldi.noduri;

	this->ldi.noduri = nodNou;
}

// constructor multidictionar
// Complexitate de timp: θ(1)
//
MD::MD() {
	/* de adaugat */
	this->ldi.cp = 2;
	this->ldi.n = 0;
	this->ldi.prim = -1;
	this->ldi.ultim = -1;
	this->ldi.primGol = 0;
	this->ldi.noduri = new Nod[this->ldi.cp];
	
	for (int i = 0;i < this->ldi.cp - 1;i++) {
		this->ldi.noduri[i].urm = i + 1;
	}
	this->ldi.noduri[this->ldi.cp - 1].urm = -1;

	for (int i = 1;i < this->ldi.cp;i++) {
		this->ldi.noduri[i].prec = i - 1;
	}
	this->ldi.noduri[0].prec = -1;

}


// aloca spatiu pentru un nod nou
// returneaza pozitia unde se va adauga nodul
// Complexitate de timp: θ(1)
//
int MD::aloca() {
	//se sterge primul element din lista spatiului liber
	int i = this->ldi.primGol;
	if (i != -1) {
		this->ldi.noduri[this->ldi.primGol].prec = -1;
		this->ldi.primGol = this->ldi.noduri[this->ldi.primGol].urm;
		this->ldi.noduri[i].urm = -1;
		this->ldi.noduri[i].prec = -1;
	}
	return i;
}


// elibereaza un nod din lista de noduri de pe pozitia i 
// este folosita la stergere
// Complexitate de timp: θ(1)
//
void MD::dealoca(int i) {
	//se trece pozitia i in lista spatiului liber
	this->ldi.noduri[i].urm = this->ldi.primGol;
	this->ldi.noduri[i].prec = -1;
	this->ldi.noduri[this->ldi.primGol].prec = i;
	this->ldi.primGol = i;
}


// adauga la inceput un nod nou
// redimensioneaza daca este cazul
// Caz defavorabil: θ(n) cand se face redimensionare
// Caz favorabil:θ(1) nu se face redimensionare
// Caz mediu:O(n)
//
void MD::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	int newElem = aloca();
	if (newElem == -1) {
		redim();
		newElem = aloca();
	}

	this->ldi.noduri[newElem].e = std::make_pair(c,v);
	
	if (this->ldi.prim == -1) {
		this->ldi.prim = newElem;
		this->ldi.ultim = newElem;
	}
	else {
		this->ldi.noduri[newElem].urm = this->ldi.prim;
		this->ldi.noduri[this->ldi.prim].prec = newElem;
		this->ldi.prim = newElem;
	}
	this->ldi.n += 1;
}

// sterge un nod dupa cheie si valoare
// Caz favorabil:θ(1) perechea cautata se afla pe prima pozitie
// Caz defavorabil:θ(n) perechea cautata se afla pe ultima pozitie
// Caz mediu:O(n) perechea cautata se afla undeva in mijlocul MD-ului
//
bool MD::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	int curentNod = this->ldi.prim;
	int precNod = -1;
	while (curentNod != -1) {
		if (this->ldi.noduri[curentNod].e.first == c && this->ldi.noduri[curentNod].e.second == v) {
			if (curentNod == this->ldi.prim) {
				this->ldi.prim = this->ldi.noduri[curentNod].urm;
			}
			if (curentNod == this->ldi.ultim) {
				this->ldi.ultim = this->ldi.noduri[curentNod].prec;
			}
			if (this->ldi.noduri[curentNod].urm != -1) {
				this->ldi.noduri[precNod].urm = this->ldi.noduri[curentNod].prec;
			}
			if (this->ldi.noduri[curentNod].prec != -1) {
				this->ldi.noduri[precNod].urm = this->ldi.noduri[curentNod].urm;
			}
			this->dealoca(curentNod);
			this->ldi.n -= 1;
			return true;
		}
		precNod = curentNod;
		curentNod = this->ldi.noduri[curentNod].urm;
	}
	return false;
}

// cauta in MD toate nodurile care au cheia c
// returneaza un vector cu toate valorile asociate cheii c
//
// CF = CD = CM =  θ(n) se parcurge tot MD
//
vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */
	vector<TValoare> val;
	int curentNod = this->ldi.prim;
	while (curentNod != -1) {
		if (this->ldi.noduri[curentNod].e.first == c) {
			val.push_back(this->ldi.noduri[curentNod].e.second);
		}
		curentNod = this->ldi.noduri[curentNod].urm;
	}
	return val;
}

// returneaza numarul de perechi (cheie, valoare) din MD 
// Complexitate timp:θ()
//
int MD::dim() const {
	/* de adaugat */
	return this->ldi.n;
}

// verifica daca multidictionarul este vid
// Complexitate timp:θ(1)
//
bool MD::vid() const {
	/* de adaugat */
	return this->dim() == 0;
}
// returneaza valoarea care apare cel mai frecvent in MD
// daca apar mai multe valori cu frecvente identice se returneaza 
// doar o valoare
// daca MD-ul este vid se returneaza NULL_TValoare
// 
// 
// subalgoritm ceaMaiFrecventa()
//    intreg ok
//    TValoare vMax
//	  intreg fMax = -99, f
//	  vector<TValoare> valori
// 
//    daca MD-ul este vid atunci returneaza NULL_TValoare
// 
//    intreg Nodcurent = prim
// 
//    cat timp Nodcurent != -1 executa
//			ok = 1
// 
//			pentru v in valori executa
//				daca Nodcurent.valoare == v atunci ok=0
//			sf pentru
// 
//			daca ok==1 atunci adaugam in vectorul valoare Nodcurent.valoare
//			Nodcurent = Nodcurent.urmator
// 
//	  sf cat timp
//    
//    pentru v in valori executa
//			intreg Nodcurent = prim
//			f = 0
// 
//			cat timp Nodcurent != -1 executa
//				daca Nodcurent.valoare == v atunci f = f + 1
//				Nodcurent = Nodcurent.urmator
//			sf cat timp
// 
//			daca f > fmax atunci 
//				fmax = f
//				vMax = v
//			sf daca
// 
//    sf pentru
//   
//    returneaza vMax
// 
// 
// Complexitate timp:
// 
// Caz favorabil: θ(n) daca toate valorile din MD sunt identice
// Caz defavorabil: θ(n^2) daca toate valorile din MD sunt unice
// Caz mediu: O(n * m) daca unele valori sunt unice unde n-numarul de el. din MD si m-numarul de valori unice din MD
//
TValoare MD::ceaMaiFrecventa() const {
	int ok;
	TValoare vMax;
	int fMax=-99,f;
	vector<TValoare> val;
	
	if (vid()) return NULL_TVALUE;

	int curentNod = this->ldi.prim;
	while (curentNod != -1) {
		ok = 1;
		for (auto v : val) {
			if (this->ldi.noduri[curentNod].e.second == v)
				ok = 0;
		}
		if (ok == 1)val.push_back(this->ldi.noduri[curentNod].e.second);
		curentNod = this->ldi.noduri[curentNod].urm;
	}

	for (auto v : val) {
		int curentNod = this->ldi.prim;
		f = 0;

		while (curentNod != -1) {
			if (this->ldi.noduri[curentNod].e.second == v)f += 1;
			curentNod = this->ldi.noduri[curentNod].urm;
		}

		if (f > fMax) {
			fMax = f;
			vMax = v;
		}
	}
	return vMax;
	
}

// returneaza un iterator pe multidictionar
// Complexitate timp:θ(1)
//
IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

// deconstructor pentru multidictionar
// Complexitate timp:θ(1)
//
MD::~MD() {
	/* de adaugat */
	delete[] this->ldi.noduri;
}

