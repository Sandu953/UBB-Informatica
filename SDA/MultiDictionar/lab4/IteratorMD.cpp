#include "IteratorMD.h"
#include "MD.h"

using namespace std;


IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	/* de adaugat */
	ldi = md.ldi;
	curent = md.ldi.prim;
}

TElem IteratorMD::element() const {
	/* de adaugat */
	if (valid())
		return ldi.noduri[curent].e;
	else
		throw std::runtime_error("Iterator invalid!");
}

bool IteratorMD::valid() const {
	/* de adaugat */
	return curent!=-1;
}

void IteratorMD::urmator() {
	/* de adaugat */
	if (valid())
		curent = ldi.noduri[curent].urm;
	else
		throw std::runtime_error("Iterator invalid!");
}

void IteratorMD::prim() {
	/* de adaugat */
	curent = md.ldi.prim;
}

