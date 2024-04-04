#include "disciplina.h"


bool cmpDenumire(const Disciplina& d1, const Disciplina& d2) {
	return d1.getDenumire() < d2.getDenumire();
}

bool cmpOre(const Disciplina& d1, const Disciplina& d2) noexcept {
	return d1.getOre() < d2.getOre();
}

bool cmpCadru_Tip(const Disciplina& d1, const Disciplina& d2) {
	if (d1.getCadru() == d2.getCadru())
		return d1.getTip() < d2.getTip();
	return d1.getCadru() < d2.getCadru();
}
