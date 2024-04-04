#pragma once

#define NULL_TELEM -1111111111
#define NULL_TVALOARE -1
typedef int TElem;

class IteratorColectie;

typedef struct Nod {
	TElem e;
	int urm;
} Nod;


class Colectie
{
	friend class IteratorColectie;

private:
	
	Nod* noduri;
	int m;
	int cp;
	int primLiber;
	//actualizare primLiber
	void actPrimLiber();
	//functia de dispersie
	int d(TElem e);
	void redim();
	

public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	int valoareMaxima() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};

