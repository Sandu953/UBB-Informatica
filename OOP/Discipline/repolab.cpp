#include "repolab.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <cstdlib>



using std::ostream;
using std::stringstream;

void RepoLab::store(const Disciplina& d) {


	throwExceptionWithProbability();
	if (exist(d)) {
		throw DisRepoExceptionLab("Exista deja disciplina: " + d.getDenumire() + "!");
	}
	//all.push_back(d);
	allm.insert({ d.getDenumire(),d });
	all.push_back(d);

}

void RepoLab::deleteDis(string denumire) {

	throwExceptionWithProbability();
	for (std::pair<string, Disciplina> pereche : this->allm) {
		if (pereche.first == denumire) {
			allm.erase(denumire);
			return;
		}

	}
	for (int i = 0;i < all.size();i++)
		if (all[i].getDenumire() == denumire)
		{
			all.erase(all.begin() + i);
		}
	//erase from all vector as well
}

bool RepoLab::exist(const Disciplina& d) {

	throwExceptionWithProbability();
	try {
		find(d.getDenumire());
		return true;
	}
	catch (DisRepoExceptionLab&) {
		return false;
	}
}

void RepoLab::throwExceptionWithProbability()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution <> dist(0, 1);
	double nrRand = dist(mt);
	cout << "Numarul generat:" << nrRand << std::endl;
	if (nrRand < sansa)
		throw DisRepoExceptionLab("Mai incearca!");

}

const Disciplina& RepoLab::find(string denumire) {

	throwExceptionWithProbability();
	if (this->allm.find(denumire) != this->allm.end())
		return this->allm[denumire];

	throw DisRepoExceptionLab("Nu exista disciplina: " + denumire);
}

void RepoLab::modDis(string denumire, int ora) {

	throwExceptionWithProbability();
	cout << ora;
	for (auto& d : allm) {
		if (d.second.getDenumire() == denumire) {
			d.second.setOre(ora);
		}
	}
	/*for (std::map< Disciplina, int>::iterator it = allm.begin(); it != allm.end(); ++it) {
		if (it->first.getDenumire() == denumire)
			it->first.setOre(ora);
	}*/
	//modify in all vector as well
	for (auto& d : all) {
		if (d.getDenumire() == denumire) {
			d.setOre(ora);
		}
	}
}


/*
returneaza toate disciplinele salvate
*/
const vector<Disciplina>& RepoLab::getAll() const {

	//	vector<Disciplina> ret;
	//	for (auto& d : allm) {
	//		ret.push_back(d.first);
	//	}
	//	return ret;g
	//}
	return this->all;
}

ostream& operator<<(ostream& out, const DisRepoExceptionLab& ex) {
	out << ex.msg;
	return out;
}
