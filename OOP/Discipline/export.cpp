#include "export.h"
#include "disciplina.h"
#include "disrepo.h"
#include <fstream>
#include <string>
#include <vector>
/*
Scrie in fisierul fName lista de disicipline
in format Comma Separated Values
arunca DisRepoException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Disciplina>& disc) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw DisRepoException("Unable to open file:" + fName);
	}
	for (const auto& d : disc) {
		out << d.getDenumire() << ",";
		out << d.getOre() << ",";
		out << d.getTip() << ",";
		out << d.getCadru() << std::endl;
	}
	out.close();
}