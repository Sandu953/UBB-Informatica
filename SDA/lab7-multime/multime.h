#pragma once
#include <iostream>
#include <math.h>
#define NULL_TELEM -INFINITY

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

typedef struct Nod {
	TElem e;
	int st;
	int dr;
} Nod;


class Multime {

	friend class IteratorMultime;

private:
	Nod* arbore;
	int primLiber;
	int cp;
	int rad;
	int dimensiune;

	//functie de redimensionare
	void redim();

	TElem minim(int rad) const;
	TElem maxim(int rad) const;

	int stergeRec(int rad, TElem e,bool& sters);

	//functie de resetare a primului liber
	


public:

	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	//returneaza diferenta dintre maxim si minim
	//returneaza -1 daca multimea e vida
	int diferențaMaxMin() const;


	// destructorul multimii
	~Multime();

};



