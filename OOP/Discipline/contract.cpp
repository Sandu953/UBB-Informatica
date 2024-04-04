#include "contract.h"

using std::shuffle;

void Contract::addDisContract(const Disciplina& d) {
	this->contract.push_back(d);
	notify();
}

void Contract::golesteContract() {
	this->contract.clear();
	notify();
}

const vector<Disciplina>& Contract::allContract() {
	return this->contract;
}

void Contract::random(vector<Disciplina> discipline, int cate) {
	shuffle(discipline.begin(), discipline.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (contract.size() < cate && discipline.size() > 0) {
		contract.push_back(discipline.back());
		discipline.pop_back();
	}
	notify();
}

