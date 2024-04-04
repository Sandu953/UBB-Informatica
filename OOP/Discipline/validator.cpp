#include "validator.h"
#include <assert.h>
#include <sstream>

void DisciplinaValidator::validate(const Disciplina& d) {
	vector<string> msgs;
	if (d.getDenumire().size() == 0) msgs.push_back("Denumirea nu poate fi vida!");
	if (d.getOre() < 0)msgs.push_back("Ore negative!!!!");
	if (d.getTip().size() == 0)msgs.push_back("Tipul nu poate fi vid!");
	if (d.getCadru().size() == 0)msgs.push_back("Cadrul didactic nu poate fi vid!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	DisciplinaValidator v;
	Disciplina d{ "",-2,"","" };
	try {
		v.validate(d);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto const mesaj = sout.str();
		assert(mesaj.find("negative") >= 0);
		assert(mesaj.find("vid") >= 0);
		assert(mesaj.find("vida") >= 0);
	}

}