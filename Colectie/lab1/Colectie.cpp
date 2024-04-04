#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <new>

using namespace std;

bool rel(TElem e1, TElem e2) {
    if (e1 <= e2)return true;
    return false;
}

void Colectie::redim() {
    /*
    * Complexitate timp:
    * caz favorabil = caz mediu = caz defavorabil = θ(n);
    */

    //alocam un spatiu de capacitate dubla
    TElem* eNou = new int[2 * cp];

    //copiem vechile valori in noua zona
    for (int i = 0; i < n; i++)
        eNou[i] = e[i];

    //dublam capacitatea
    cp = 2 * cp;

    //eliberam vechea zona
    delete[] e;

    //vectorul indica spre noua zona
    e = eNou;
}

Colectie::Colectie() {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */

    //setam capacitatea
    this->cp = 2;

    //alocam spatiu de memorare pentru vector
    e = new TElem[cp];

    //setam numarul de elemente
    this->n = 0;
}

void QuickSort(TElem v[], int st, int dr)
{
    /*
   * Complexitate timp:
   * caz favorabil = O(n logn)lista este deja sortata;
   * caz mediu =  O(n logn)lista este amestecata;
   * caz defavorabil = θ(n^2)lista este sortata descrescator;
   */
    if (st < dr)
    {
        //pivotul este inițial v[st]
        int m = (st + dr) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;
        int i = st, j = dr, d = 0;
        while (i < j)
        {
            if (rel(v[i],v[j])==false)
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort(v, st, i - 1);
        QuickSort(v, i + 1, dr);
    }
}

void Colectie::adauga(TElem e) {
    /*
   * Complexitate timp:
   * caz favorabil = O(n logn);
   * caz mediu =  O(n logn);
   * caz defavorabil = θ(n^2);
   */

    //daca s-a atins capacitatea maxima, redimensionam
    if (n == cp)
        redim();

    //adaugam la sfarsit
    this->e[n++] = e;
    QuickSort(this->e, 0, this->n-1);
}


bool Colectie::sterge(TElem e) {
    /*
   * Complexitate timp:
   * caz favorabil = O(1) daca el. sters se afla pe prima pozitie;
   * caz mediu =  O(n) el se afla undeva in interiorul colectiei;
   * caz defavorabil = θ(n) el se afla pe ultima pozitie;
   * caz general = O(n);
   */

    IteratorColectie i = iterator();
    //parcurgem cloectia
    while (i.valid()) {
        //daca gasim elementul
        if (e == i.element()) {
            //mutam elementul la final
            for (int j = i.curent;j < this->n;j++) {
                this->e[j] = this->e[j + 1];
            }
            //decrementam dimensiunea
            this->n -= 1;
            return true;
        }
        i.urmator();
    }
    //returnam false daca el. nu se afla in colectie
    return false;

}


bool Colectie::cauta(TElem elem) const {
    /*
  * Complexitate timp:
  * caz favorabil = caz mediu = caz defavorabil = θ(n);
  * chiar daca el se afla pe prima pozitie din colectie trebuie mutat 
  * la finalul colectiei deci va avea complexitate θ(n) indiferent de 
  * pozitia in colectie
  */

    IteratorColectie i = iterator();
    //parcurgem colectia
    while (i.valid()) {
        //daca il gasim returneaza true 
        if (elem == i.element()) {
            return true;
        }
        i.urmator();
    }
    //returnam false daca nu il gasim
    return false;
}


int Colectie::nrAparitii(TElem elem) const {
    /*
  * Complexitate timp:
  * caz favorabil = O(1) daca el. sters se afla pe prima pozitie;
  * caz mediu =  O(n) el se afla undeva in interiorul colectiei;
  * caz defavorabil = θ(n) el se afla pe ultima pozitie;
  * caz general = O(n);
  */

    IteratorColectie i = iterator();
    int nr = 0;
    //parcurgem colectia
    while (i.valid()) {
        //daca gasim elementul incrementam nr
        if (elem == i.element()) {
            nr += 1;
        }
        i.urmator();
    }
    //returnam nr de aparitii
    return nr;
}

bool Colectie::adaugaAparitiiMultiple(int nr,TElem elem) {
    /*
    * adaugaAparitiiMultiple(c, nr, elem)
    *   pre: c-o colectie, nr-int, elem-TElement
    *   post: c'- o colectie;c'=c+{elem de nr ori}
    *   {s-a adaugat elementul elem de nr ori}
    *   {returneaza adevarat daca elementele s-au adaugat cu succes si fals in caz contrar}
    * 
    * Subalgoritm adaugaAparitiiMultiple(int nr,TElem elem){
    *   Daca nr<0 returneaza fals
    *   Pentru i=0,i<nr executa
    *       @adaugare element
    *   SfPentru
    *   returneaza adevarat
    * SfSubalgoritm
    * 
    * }
    */

    /*
    * Complexitate timp:
    * caz favorabil = caz mediu = θ(nr * nlogn)
    * cad defavorabil = θ(nr * n^2)
    * in adaugare folosesc functia de sortare QuickSort
    */
    if (nr < 0)
        // daca nr este negativ returneaza false
        return false;
    for (int i = 0;i < nr;i++)
        //pentru nr ori adaugam elem
        adauga(elem);
    //returunam true daca elementele s-au adaugat cu succes
    return true;
}


int Colectie::dim() const {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */
    return n;
}


bool Colectie::vida() const {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */
    if (n != 0) return false;
    return true;
}


IteratorColectie Colectie::iterator() const {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */
    return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    /*
   * Complexitate timp:
   * caz favorabil = caz mediu = caz defavorabil = θ(1);
   */
    //eliberam zona de memorare alocata vectorului
    delete[] e;
}
