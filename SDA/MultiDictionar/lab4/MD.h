#pragma once
#include<vector>
#include<utility>

using namespace std;

#define NULL_TVALUE -1;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

typedef struct Nod {
	TElem e;
	int urm, prec;
} Nod;

typedef struct LDI {
	Nod* noduri;
	int cp, prim, ultim, primGol, n;
} LDI;



class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	LDI ldi;

	int aloca();
	void dealoca(int i);
	void redim();

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	TValoare ceaMaiFrecventa() const ;

	// destructorul MultiDictionarului	
	~MD();



};



