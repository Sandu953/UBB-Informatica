#include "facultate.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <unordered_map>
#include "undo.h"




//vector<Disciplina> Facultate::generalSort(bool(*maiMicF)(const Disciplina&, const Disciplina&)) {
//	vector<Disciplina> v{ rep.getAll() };//fac o copie	
//	for (size_t i = 0; i < v.size(); i++) {
//		for (size_t j = i + 1; j < v.size(); j++) {
//			if (!maiMicF(v[i], v[j])) {
//				//interschimbam
//				Disciplina aux = v[i];
//				v[i] = v[j];
//				v[j] = aux;
//			}
//		}
//	}
//	return v;
//}


//std::map<std::string, DTO> dic;


void Facultate::addDis(const string& denumire, int ore, const string& tip, const string& cadru) {
	Disciplina d{ denumire,ore,tip,cadru };
	val.validate(d);
	rep.store(d);
	//dic.insert({ tip, DTO });
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, d));


}

void Facultate::stergeDis(const string& denumire) {

	undoActions.push_back(std::make_unique<UndoSterge>(rep, rep.find(denumire)));
	rep.deleteDis(denumire);
}

void Facultate::modifica(const string& denumire, int ore) {
	undoActions.push_back(std::make_unique<UndoModificare>(rep, rep.find(denumire), rep.find(denumire).getOre()));
	rep.modDis(denumire, ore);
}

void Facultate::undo() {
	if (undoActions.empty()) {
		throw DisRepoException{ "Nu mai exista operatii" };
	}
	/*
	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
	*/
	// Varianta cu unique_ptr
	//obs: la obiecte unique_ptr nu putem face copie
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

int Facultate::cauta(const string& denumire) {

	return rep.find(denumire).getDenumire() != "";


}



vector<Disciplina> Facultate::sortByDenumire() {
	//auto copyAll = rep.getAll();
	////std::sort(copyAll.begin(), copyAll.end(), cmpDenumire);
	//return generalSort(cmpDenumire);
	////return copyAll;
	vector<Disciplina> sortedCopy{ rep.getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpDenumire);
	return sortedCopy;

}

vector<Disciplina> Facultate::sortByOre() {
	//return generalSort(cmpOre);
	vector<Disciplina> sortedCopy{ rep.getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpOre);
	return sortedCopy;

}



vector<Disciplina> Facultate::sortByCadruTip() {
	//return generalSort(cmpCadru_Tip);
	vector<Disciplina> sortedCopy{ rep.getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpCadru_Tip);
	return sortedCopy;
}

//vector<Disciplina> Facultate::filtreaza(function<bool(const Disciplina&)> fct) {
//	
//	/*for (const auto& dis : rep.getAll()) {
//		if (fct(dis)) {
//			rez.push_back(dis);
//		}
//	}*/
//	const vector<Disciplina>& all = getAll();
//	vector<Disciplina> rez;
//	std::copy_if(all.begin(),all.end(),back_inserter(rez),
//		[])
//	return rez;
//}

vector<Disciplina> Facultate::filtrareOreMaiMulte(int ore) {
	/*return filtreaza([ore](const Disciplina& d) {
		return d.getOre() > ore;
		});*/
	const vector<Disciplina>& all = getAll();
	vector<Disciplina> rez;
	std::copy_if(all.begin(), all.end(), back_inserter(rez),
		[ore](const Disciplina& d) {
			return d.getOre() > ore;
		});
	return rez;

}

vector<Disciplina> Facultate::filtrareCadru(const string& cadru) {
	/*return filtreaza([cadru](const Disciplina& d) {
		return d.getCadru() == cadru;
		});*/
	const vector<Disciplina>& all = getAll();
	vector<Disciplina> rez;
	std::copy_if(all.begin(), all.end(), back_inserter(rez),
		[cadru](const Disciplina& d) {
			return d.getCadru() == cadru;
		});
	return rez;

}

void Facultate::adaugaLaContract(string denumire)
{
	const auto& dis = rep.find(denumire);
	contractFacultate.addDisContract(dis);

}

void Facultate::golesteContract() {
	contractFacultate.golesteContract();
}

const vector<Disciplina>& Facultate::allContract() {
	return contractFacultate.allContract();
}



int Facultate::adaugaRandom(int cate) {
	int inainte = (int)contractFacultate.allContract().size();
	contractFacultate.random(this->getAll(), cate);
	return (int)(contractFacultate.allContract().size() - inainte);
}

vector<std::string> Facultate::tipunic() {
	vector<std::string> ret;
	for (auto& d : getAll()) {
		int ok = 1;
		for (auto& s : ret) {
			if (d.getTip() == s) ok = 0;
		}
		if (ok == 1) ret.push_back(d.getTip());
	}
	return ret;
}

int Facultate::nrtip(const string& tip) {
	int nr = 0;
	for (auto& d : getAll()) {
		if (d.getTip() == tip)
			nr = nr+1;
	}
	return nr;
}


void Facultate::exportContractCVS(std::string fName) {
	exportToCVS(fName, contractFacultate.allContract());
}

void testAdaugaCtr() {
	DisRepo rep;
	DisciplinaValidator val;
	Facultate ctr{ rep,val };
	ctr.addDis("a", 6, "a", "a");

	assert(ctr.getAll().size() == 1);

	try {
		ctr.addDis("", -1, "", "");
	}
	catch (ValidateException&) {
		assert(true);
	}

}

void testFiltrare() {
	DisRepo rep;
	DisciplinaValidator val;
	Facultate ctr{ rep,val };
	ctr.addDis("a", 6, "a", "a");
	ctr.addDis("b", 7, "b", "b");
	ctr.addDis("c", 8, "c", "a");
	assert(ctr.cauta("a") == 1);
	try {
		ctr.cauta("t");
	}
	catch (DisRepoException&) {
		assert(true);
	}
	assert(ctr.filtrareOreMaiMulte(6).size() == 2);
	assert(ctr.filtrareOreMaiMulte(10).size() == 0);
	assert(ctr.filtrareCadru("a").size() == 2);
	assert(ctr.filtrareCadru("b").size() == 1);
	assert(ctr.filtrareCadru("c").size() == 0);
}

void testSortare() {
	DisRepo rep;
	DisciplinaValidator val;
	Facultate ctr{ rep,val };
	ctr.addDis("a", 6, "a", "a");
	ctr.addDis("b", 7, "b", "b");
	ctr.addDis("c", 8, "c", "a");

	auto firstP = ctr.sortByDenumire()[0];
	assert(firstP.getDenumire() == "a");

	firstP = ctr.sortByOre()[0];
	assert(firstP.getOre() == 6);

	firstP = ctr.sortByCadruTip()[0];
	assert(firstP.getCadru() == "a");

}

void testContract() {
	DisRepo rep;
	DisciplinaValidator val;
	Facultate ctr{ rep,val };
	ctr.addDis("a", 6, "a", "a");
	ctr.addDis("b", 7, "b", "b");
	ctr.addDis("c", 8, "c", "a");

	ctr.adaugaLaContract("a");
	assert(ctr.allContract().size() == 1);
	ctr.golesteContract();
	assert(ctr.allContract().size() == 0);
	ctr.adaugaRandom(2);
	assert(ctr.allContract().size() == 2);
	ctr.exportContractCVS("contractetest.txt");


}

void testUndo() {
	std::ofstream out("testundo.txt", std::ios::trunc);
	out.close();//creez un fisier gol
	RepoFile rep{ "testundo.txt" };
	DisciplinaValidator val;
	Facultate ctr{ rep,val };
	ctr.addDis("a", 6, "a", "a");
	ctr.addDis("b", 7, "b", "b");
	ctr.addDis("c", 8, "c", "a");
	assert(ctr.getAll().size() == 3);
	ctr.undo();
	assert(ctr.getAll().size() == 2);
	ctr.stergeDis("b");
	ctr.undo();
	assert(ctr.getAll().size() == 2);
	ctr.modifica("a", 8);
	assert(ctr.getAll()[0].getOre() == 8);
	ctr.undo();
	assert(ctr.getAll()[0].getOre() == 6);

}




void testCtr() {
	testAdaugaCtr();
	testFiltrare();
	testSortare();
	testContract();
	testUndo();
}
