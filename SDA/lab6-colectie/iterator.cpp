#include "iterator.h"
#include "colectie.h"

/// 
/// gaseste urmatorul el. din colectie
/// Caz favorabil:exiata un el. chiar pe pozitia curent+1: θ(1)
/// Caz defavorabil: urmatorul e. este chiar la finalul colectiei: θ(n)
///
void IteratorColectie::deplasare() {
	while ((curent < col.m) && col.noduri[curent].e == NULL_TELEM)
		curent++;
}

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	curent = 0;
	deplasare();
}

void IteratorColectie::prim() {
	/* de adaugat */
	curent = 0;
	deplasare();
}


void IteratorColectie::urmator() {
	/* de adaugat */
	curent++;
	deplasare();
}


bool IteratorColectie::valid() const {
	/* de adaugat */
	return (curent < col.m);
}



TElem IteratorColectie::element() const {
	/* de adaugat */
	return col.noduri[curent].e;
}
