#pragma once
#include "disciplina.h"
#include "repoabs.h"
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

using std::vector;
using std::string;
using std::ostream;

class DisRepo :public RepoAbstract {
	vector<Disciplina> all;
	/*
	metoda privata verifica daca exista deja d in repository
	*/
	bool exist(const Disciplina& d) override;

public:
	DisRepo() = default;
	//nu permitem copierea de obiecte
	DisRepo(const DisRepo& ot) = delete;
	/*
	Salvare disciplina
	arunca exceptie daca mai exista o disciplina cu aceeasi denumire
	*/
	virtual void store(const Disciplina& p) override;

	/*
	* sterge o disciplina
	*/
	virtual void deleteDis(string denumire) override;

	virtual void modDis(string denumire, int ora)override;

	/*
	Cauta o disciplina
	arunca exceptie daca nu exista disiplina
	*/
	const Disciplina& find(string denumire) override;

	/*
	returneaza toate disciplinele salvate
	*/
	const vector<Disciplina>& getAll() const noexcept override;


};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class DisRepoException {
	
public:
    string msg;
	DisRepoException(string m) :msg{ m } {}
	string getMsg() const { return msg; }
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const DisRepoException& ex);
};

ostream& operator<<(ostream& out, const DisRepoException& ex);


class RepoFile :public DisRepo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	RepoFile(std::string fName) :DisRepo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	void store(const Disciplina& d) override {
		DisRepo::store(d);//apelam metoda din clasa de baza
		writeToFile();
	}
	void deleteDis(const string denumire) override {
		DisRepo::deleteDis(denumire);//apelam metoda din clasa de baza
		writeToFile();
	}
	void modDis(string denumire, int ora) override {
		DisRepo::modDis(denumire, ora);
		writeToFile();
	}
};


void testeRepo();
