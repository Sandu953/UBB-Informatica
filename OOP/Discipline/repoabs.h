#pragma once
#include "disciplina.h"
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

using std::vector;
using std::string;
using std::ostream;


class RepoAbstract
{
	/*
	metoda privata verifica daca exista deja d in repository
	*/
	virtual bool exist(const Disciplina& d) = 0;
public:
	virtual void store(const Disciplina& p) = 0;

	/*
	* sterge o disciplina
	*/
	virtual void deleteDis(string denumire) = 0;

	virtual void modDis(string denumire, int ora) = 0;

	/*
	Cauta o disciplina
	arunca exceptie daca nu exista disiplina
	*/
	virtual const Disciplina& find(string denumire) = 0;

	/*
	returneaza toate disciplinele salvate
	*/
	virtual const vector<Disciplina>& getAll() const = 0;

	virtual ~RepoAbstract() {};
};


