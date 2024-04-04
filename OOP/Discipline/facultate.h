#pragma once
#include "disciplina.h"
#include "disrepo.h"
#include "validator.h"
#include "contract.h"
#include "export.h"
#include <string>
#include <vector>
#include <functional>
#include <map>
#include "undo.h"


using std::vector;
using std::function;

using std::unique_ptr;

class Facultate {





	DisciplinaValidator& val;

	/*
	 Functie de sortare generala
	 maiMicF - functie care compara doua discipline, verifica daca are loc relatia mai mic
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Disciplina)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Disciplina> generalSort(bool (*maiMicF)(const Disciplina&, const Disciplina&));

	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar disciplinele care trec de filtru (fct(pet)==true)
	*/
	vector<Disciplina> filtreaza(function<bool(const Disciplina&)> fct);

	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	Contract contractFacultate;

public:
	RepoAbstract& rep;
	Facultate(RepoAbstract& rep, DisciplinaValidator& val) : rep{ rep }, val{ val } {}

	//nu permitem copierea de obiecte Facultate
	Facultate(const Facultate& ot) = delete;

	/*
	 returneaza toate disciplinele in ordinea in care au fost adaugate
	*/
	const vector<Disciplina>& getAll() noexcept {
		return rep.getAll();
	}

	/*
	Adauga o noua disciplina
	arunca exceptie daca: nu se poate salva, nu este valida
	*/
	void addDis(const string& denumire, int ore, const string& tip, const string& cadru);

	void stergeDis(const string& denumire);

	void modifica(const string& denumire, int oreNoua);

	vector<std::string> tipunic();

	int nrtip(const string& tip);

	/*
	Cauta o disciplina
	Returneaza 1 daca exista, 0 in caz contrar
	*/
	int cauta(const string& denumire);
	/*
	Sorteaza dupa denumire
	*/
	vector<Disciplina> sortByDenumire();

	/*
	Sorteaza dupa ore
	*/
	vector<Disciplina> sortByOre();


	/*
	Sorteaza dupa cadru + tip
	*/
	vector<Disciplina> sortByCadruTip();

	/*
	returneaza doar disciplinele cu ore mai multe decat un nr dat
	*/
	vector<Disciplina> filtrareOreMaiMulte(int ore);

	/*
	returneaza doar disciplinele care au un cadru didactic dat
	*/
	vector<Disciplina> filtrareCadru(const string& cadru);

	void undo();

	void adaugaLaContract(string denumire);

	int adaugaRandom(int cate);

	void golesteContract();

	const vector<Disciplina>& allContract();

	Contract& getContract()  {
		return contractFacultate;
	}

	void exportContractCVS(std::string fName);
};
void testCtr();




