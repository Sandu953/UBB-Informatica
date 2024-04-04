#pragma once
#include "disciplina.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"


using std::vector;


class Contract : public Observable
{
private:
	vector<Disciplina> contract;
public:
	Contract() = default;

	/*
	* Adauga o disciplina in contract
	*
	*/
	void addDisContract(const Disciplina& d);

	/*
	* Goleste contractul
	*/
	void golesteContract();

	/*
	* Adauga in contract un numar dat de discipline
	*/
	void random(vector<Disciplina> discipline, int cate);

	/*
	* Returneaza toate disciplinele din contract
	*/
	const vector<Disciplina>& allContract();
};

