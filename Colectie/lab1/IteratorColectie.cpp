#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */

    //- pointer spre primul element din vector
    curent = 0;
}

TElem IteratorColectie::element() const {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */

    //elementul curent
    return col.e[curent];
    return -1;
}

bool IteratorColectie::valid() const {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */

    //verifica daca iteratorul indica spre un element al vectorului
    return curent < col.dim();
    return false;
}

void IteratorColectie::urmator() {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */

    //verifica daca iteratorul indica spre un element al vectorului
    curent++;
}

void IteratorColectie::prim() {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */

    //- pointer spre primul element din vector
    curent = 0;
}
