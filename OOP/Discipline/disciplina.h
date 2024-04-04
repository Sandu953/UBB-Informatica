#pragma once
#include <iostream>
#include <string>

using std::string;
using std::cout;

class Disciplina {
	std::string denumire;
	int ore;
	std::string tip;
	std::string cadru;
public:
	Disciplina() = default;
	Disciplina(const string d, int o, const string t, const string c) :denumire{ d }, ore{ o }, tip{ t }, cadru{ c } {}
	Disciplina(const Disciplina& ot) :denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadru{ ot.cadru } {
		//cout << "Copiere!!!";
	}

	string getDenumire() const {
		return denumire;
	}

	int getOre() const noexcept {
		return ore;
	}

	string getTip() const {
		return tip;
	}

	string getCadru() const {
		return cadru;
	}

	void setOre(int ora_noua) {
		this->ore = ora_noua;
	}


};

/*
* Compara dupa denumire
* returneaza true daca d1.denumire e mai mic decat d2.denumire
*/
bool cmpDenumire(const Disciplina& d1, const Disciplina& d2);

/*
* Compara dupa ore
* returneaza true daca d1.ore e mai mic decat d2.ore
*/
bool cmpOre(const Disciplina& d1, const Disciplina& d2) noexcept;

/*
* Compara dupa cadru + tip
* returneaza true daca d1.cadru e mai mic decat d2.cadru
* daca d1.cadru este egal cu d2.cadru atunci returneaza true
* daca d1.tip e mai mic decat d2.tip
*/
bool cmpCadru_Tip(const Disciplina& d1, const Disciplina& d2);

class DisException {
	std::string msg;
public:
	DisException(const string& m) :msg{ m } {};
	string getMsg()const { return msg; }
};

