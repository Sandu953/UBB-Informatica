#include "iterator.h"
#include "multime.h"]
#include <stack>


IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	stiva = std::stack<int>{};
	prim();

}

TElem IteratorMultime::element() const {
	return mult.arbore[curent].e;
}

bool IteratorMultime::valid() const {
	return curent != -1 ;
}

void IteratorMultime::urmator() {
	if (valid()) {
		int node = stiva.top();
		stiva.pop();
		if (mult.arbore[node].dr != -1) {
			node = mult.arbore[node].dr;
			while (node != -1) {
				stiva.push(node);
				node = mult.arbore[node].st;
			}
		}
		if (stiva.empty() == false) {
			curent = stiva.top();
		}
		else {
			this->curent = -1;
		}
	}
}


void IteratorMultime::prim() {
	curent = mult.rad;
	if (!stiva.empty()) {
		while (!stiva.empty()) {
			stiva.pop();
		}
	}
	while (curent != -1) {
		stiva.push(curent);
		curent = mult.arbore[curent].st;
	}
	if (stiva.empty() == false) {
		curent = stiva.top();
	}
	else {
		curent = -1;
	}
}


