#include "disrepo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;


void RepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw DisRepoException("Unable to open file:" + fName);
	}
	while (!in.eof()) {
		std::string denumire;
		in >> denumire;

		int ore;
		in >> ore;

		std::string tip;
		in >> tip;

		std::string cadru;
		in >> cadru;


		if (in.eof()) {	//nu am reusit sa citesc ultimul el
			break;
		}
		Disciplina d{ denumire.c_str(), ore,tip.c_str(), cadru.c_str() };
		DisRepo::store(d);
	}
	in.close();
}

void RepoFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) { //verify if the stream is opened
		std::string msg("Unable to open file:");
		throw DisRepoException(msg);
	}
	for (auto& d : getAll()) {
		out << d.getDenumire();
		out << std::endl;
		out << d.getOre();
		out << std::endl;
		out << d.getTip();
		out << std::endl;
		out << d.getCadru();
		out << std::endl;
	}
	out.close();
}

void DisRepo::store(const Disciplina& d) {
	if (exist(d)) {
		throw DisRepoException("Exista deja disciplina: " + d.getDenumire() + "!");
	}
	all.push_back(d);

}

void DisRepo::deleteDis(string denumire) {
	for (int i = 0;i < all.size();i++)
		if (all[i].getDenumire() == denumire)
		{
			all.erase(all.begin() + i);
		}

}

bool DisRepo::exist(const Disciplina& d) {
	try {
		find(d.getDenumire());
		return true;
	}
	catch (DisRepoException&) {
		return false;
	}
}

const Disciplina& DisRepo::find(string denumire) {
	/*for (const auto& d : all) {
		if (d.getDenumire() == denumire) {
			return d;
		}
	}*/
	vector<Disciplina>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Disciplina& d) {
			return d.getDenumire() == denumire;
		});
	if (f != this->all.end())
		return (*f);
	else
		//daca nu exista arunc o exceptie
		throw DisRepoException("Nu exista disciplina: " + denumire);
}

void DisRepo::modDis(string denumire, int ora) {
	for (auto& d : all) {
		if (d.getDenumire() == denumire) {
			d.setOre(ora);
		}
	}
}


/*
returneaza toate disciplinele salvate
*/
const vector<Disciplina>& DisRepo::getAll() const noexcept {
	return all;
}

ostream& operator<<(ostream& out, const DisRepoException& ex) {
	out << ex.msg;
	return out;
}

void testAdauga() {
	DisRepo rep;

	rep.store(Disciplina{ "a",4,"a","a" });
	rep.store(Disciplina{ "b",4,"b","b" });
	assert(rep.getAll().size() == 2);
	assert(rep.find("a").getDenumire() == "a");
	rep.modDis("a", 2);
	assert(rep.find("a").getOre() == 2);

	rep.store(Disciplina{ "c",4,"b","b" });
	assert(rep.getAll().size() == 3);
	rep.deleteDis("c");
	assert(rep.getAll().size() == 2);

	try {
		rep.store(Disciplina{ "a",4,"a","a" });
	}
	catch (const DisRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("c");
	}
	catch (const DisRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	DisRepo rep;
	rep.store(Disciplina{ "a",4,"a","a" });
	rep.store(Disciplina{ "b",4,"b","b" });

	auto p = rep.find("a");
	assert(p.getDenumire() == "a");

	//arunca exceptie daca nu gaseste
	try {
		rep.find("c");
	}
	catch (DisRepoException&) {
		assert(true);
	}
}



void testFileRepo() {
	std::ofstream out("test.txt", std::ios::trunc);
	out.close();//creez un fisier gol
	RepoFile repF{ "test.txt" };
	repF.store(Disciplina{ "a",4,"b","c" });

	RepoFile repF2{ "test.txt" };
	auto d = repF2.find("a");
	assert(d.getOre() == 4);
	try {
		repF2.find("2");
	}
	catch (DisRepoException&) {
	}
	repF2.deleteDis(Disciplina{ "a",4,"b","c" }.getDenumire());
	assert(repF2.getAll().size() == 0);

	assert(d.getOre() == 4);
	try {
		repF2.find("2");
	}
	catch (DisRepoException&) {
	}
	repF2.deleteDis(Disciplina{ "a",4,"b","c" }.getDenumire());
	assert(repF2.getAll().size() == 0);

	RepoFile repF3{ "test.txt" };
	assert(repF3.getAll().size() == 0);

	//fisierul nu exista si nu se poate crea (nu se creaza si directoare)
	//ar trebui sa arunce exceptie
	try {
		RepoFile repF4{ "te/st.txt" };
	}
	catch (DisRepoException&) {
	}

}

void testeRepo() {
	testAdauga();
	testCauta();
	testFileRepo();
}