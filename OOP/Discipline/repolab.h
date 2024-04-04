#pragma once
#include "disciplina.h"
#include "repoabs.h"
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <map>
#include <random>


class RepoLab :public RepoAbstract
{
	vector<Disciplina> all;
	std::map<string, Disciplina> allm;
	/*
	metoda privata verifica daca exista deja d in repository
	*/
	bool exist(const Disciplina& d) override;
	void throwExceptionWithProbability();
	double sansa;
public:
	RepoLab() = default;
	RepoLab(double sansa) : sansa{ sansa } {}
	//nu permitem copierea de obiecte
	RepoLab(const RepoLab& ot) = delete;
	/*
	Salvare disciplina
	arunca exceptie daca mai exista o disciplina cu aceeasi denumire
	*/
	void store(const Disciplina& p) override;

	/*
	* sterge o disciplina
	*/
	void deleteDis(string denumire) override;

	void modDis(string denumire, int ora)override;

	/*
	Cauta o disciplina
	arunca exceptie daca nu exista disiplina
	*/
	const Disciplina& find(string denumire) override;

	/*
	returneaza toate disciplinele salvate
	*/
	const vector<Disciplina>& getAll() const override;
};

class DisRepoExceptionLab {
	string msg;
public:
	DisRepoExceptionLab(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	string getMsg() const { return msg; }
	friend ostream& operator<<(ostream& out, const DisRepoExceptionLab& ex);
};

ostream& operator<<(ostream& out, const DisRepoExceptionLab& ex);




