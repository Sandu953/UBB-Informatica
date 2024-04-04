#include "colectie.h"
#include "iterator.h"
#include <exception>
#include <iostream>
#include <math.h>

using namespace std;

//functia care da <hashCode>-ul unui element
int hashCode(TElem e) {
	//ptr moment numarul e intreg
	return abs(e);
}

//functia de dispersie
int Colectie::d(TElem e) {
	//dispersia prin diviziune
	return hashCode(e) % cp;
}

// functie de actualizare primLiber
// Complexitate de timp: 
// Caz favorabil: primLiber nu se actualizeaza si ramane pe pozitia 0 :θ(1)
// Caz defavorabil:urmatorul el. liber se afla la finalul colectiei: θ(n)
// Caz mediu: O(n);
//
void Colectie::actPrimLiber()
{
	primLiber = 0;
	while (primLiber < cp && noduri[primLiber].e != NULL_TELEM)
		primLiber++;
}

// functie de redimensionare a colectiei
// Complexitate de timp: 
// Caz favorabil: toate el. % capacitate sunt unice θ(n)
// Caz defavorabil: toate el. % capacitate sunt egale O(n^2)
// Caz mediu O(n^2)
void Colectie::redim() {
	Nod* nodNou = new Nod[cp*3];
	for (int i = 0; i < cp*3; i++) {
		nodNou[i].e = NULL_TELEM;
		nodNou[i].urm = NULL_TELEM;

	}
	TElem* elNou = new TElem[cp];
	for (int i = 0; i < cp; i++) {
		elNou[i] = noduri[i].e;
	}
	int cpVechi = cp;
	cp = cp * 3;

	m = 1;
	primLiber = 0;

	delete[] this->noduri;
	this->noduri = nodNou;

	for (int i = 0;i < cpVechi;i++) {
		adauga(elNou[i]);
	}


	
}

/// 
/// creeaza o colectie
/// complexitate timp O(1)
/// 
Colectie::Colectie() {
	/* de adaugat */

	cp = 3;
	m = 0;
	noduri = new Nod[cp];
	for (int i = 0; i < cp; i++) {
		noduri[i].e = NULL_TELEM;
		noduri[i].urm = NULL_TELEM;
	}
	primLiber = 0;
}

/// 
/// functie de adaugare in colectie
/// Caz favorabil: pozitia pe care trebuie adaugat el. in urma functiei de dispersie este liber: θ(1)
///                si daca pozitia de adaugat este diferita de primLiber  si nu se face redim()
/// Caz defavorabil:toate el. % capacitate sunt egale si se face redim O(n^2)
/// Caz mediu:O(n)
void Colectie::adauga(TElem elem) {
	/* de adaugat */
	int i = d(elem);
	m += 1;
	if (m-1 == cp)
		redim();
	if (noduri[i].e == NULL_TELEM)	// pozitia este libera
	{
		noduri[i].e = elem;	// adaugam elementul
		if (i == primLiber)
			actPrimLiber();	// actualizam primLiber, daca este nevoie
		return;
	}
	//actPrimLiber();
	int j = NULL_TELEM;	// j va retine pozitia precedenta lui i, pentru a putea reface inlantuirea
	// daca pozitia nu este libera
	while (i != NULL_TELEM)	// iteram pana gasim capatul inlantuirii
	{
		j = i;
		i = noduri[i].urm;
	}

	

	// adaugam elementul
	noduri[primLiber].e = elem;
	noduri[j].urm = primLiber;
	actPrimLiber();

}

/// 
/// functie de stergere
/// Caz favorabil: pozitile pe care trebuie readaugate el. in urma functiei de dispersie sunt libere: θ(n)
/// Caz defavorabil:toate el. % capacitate sunt egale intre ele: θ(n^2)
/// Caz mediu:O(n^2)
/// 
bool Colectie::sterge(TElem elem) {
	if (m == 0)return false;
	Nod* nodNou = new Nod[cp];
	for (int i = 0; i < cp; i++) {
		nodNou[i].e = noduri[i].e;
		nodNou[i].urm = noduri[i].urm;
	}

	int mVechi = m;
	m = 0;

	for (int i = 0;i < cp;i++) {
		noduri[i].e = NULL_TELEM;
		noduri[i].urm = NULL_TELEM;
	}

	primLiber = 0;
	int ok = 0;

	for (int i = 0;i < cp;i++) {
		if ((nodNou[i].e != NULL_TELEM and nodNou[i].urm != NULL_TELEM)or(nodNou[i].e == NULL_TELEM and nodNou[i].urm != NULL_TELEM) or (nodNou[i].e != NULL_TELEM and nodNou[i].urm == NULL_TELEM))
		{
			if (nodNou[i].e != elem && ok == 0)
			{
				adauga(nodNou[i].e);
			}
			else if (ok == 1) {
				adauga(nodNou[i].e);
			}
			if (nodNou[i].e == elem)
				ok = 1;
		}
	}

	if (m == mVechi)
		return false;
	return true;

	delete[] this->noduri;
}

/// 
/// functie de cautare
/// Caz favorabil: el. se afla pe prima pozitie θ(1)
/// Caz defavorabil: el. se afla pe ultima pozitie θ(n)
/// Caz mediu: O(n) 
/// 
bool Colectie::cauta(TElem elem) const {
	if (m == 0) return false;
	for (int i = 0;i < cp;i++)
		if((noduri[i].e != NULL_TELEM and noduri[i].urm != NULL_TELEM) or (noduri[i].e == NULL_TELEM and noduri[i].urm != NULL_TELEM) or (noduri[i].e != NULL_TELEM and noduri[i].urm == NULL_TELEM))
		if (noduri[i].e == elem)
			return true;
	return false;
}

/// 
/// returneaza nr. de aparitii ale unui element
/// Complexitate timp θ(n)
///
int Colectie::nrAparitii(TElem elem) const {
	if (m == 0) return false;
	int nr = 0;
	for (int i = 0;i < cp;i++)
		if ((noduri[i].e != NULL_TELEM and noduri[i].urm != NULL_TELEM) or (noduri[i].e == NULL_TELEM and noduri[i].urm != NULL_TELEM) or (noduri[i].e != NULL_TELEM and noduri[i].urm == NULL_TELEM) )
		{
			if (noduri[i].e == elem)
				nr += 1;
		}
	return nr;
}

/// 
/// returneaza numarul de el. din colectie
/// Complexitate timp θ(1)
///
int Colectie::dim() const {
	return this->m;
}

/// 
/// returneaza true daca nu exista el. false in caz contrar
/// Complexitate timp θ(1)
///
bool Colectie::vida() const {
	return m == 0;
}

/// 
/// returneaza valoarea maxima din colectie
/// sau NULL_TVALOARE daca este vida
/// 
/// subalgoritm valoareMaxima
///		daca colectia este vida atunci retuneaza NULL_TVALOARE
///		intreg max = -9999
///		pentru i=0;i<capacitatea executa
///			daca nod[i].element > max atunci max = nod[i].element
///		Sf. pentru
///     returneaza max;
/// 
/// Complexitate timp: θ(n)
/// 
int Colectie::valoareMaxima() const {
	if (vida()==true)
		return NULL_TVALOARE;
	int max = -99999;
	for (int i = 0;i < cp;i++)
	{
		if (noduri[i].e > max)max = noduri[i].e;
	}
	return max;
}

/// 
/// returneaza un iterator pe colectie
/// Complexitate timp θ(1)
///
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

/// 
/// sterge colectia
/// Complexitate timp θ(1)
///
Colectie::~Colectie() {

	delete[] this->noduri;
}


