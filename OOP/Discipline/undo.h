#pragma once
#include "disciplina.h"
#include "disrepo.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Disciplina disAdauga;
	RepoAbstract& rep;
public:
	UndoAdauga(RepoAbstract& rep, const  Disciplina& d) :rep{ rep }, disAdauga{ d } {}
	void doUndo() override {
		rep.deleteDis(disAdauga.getDenumire());
	}
};

class UndoSterge : public ActiuneUndo {
	Disciplina disSters;
	RepoAbstract& rep;
public:
	UndoSterge(RepoAbstract& rep, const  Disciplina& d) :rep{ rep }, disSters{ d } {}
	void doUndo() override {
		rep.store(disSters);
	}
};

class UndoModificare : public ActiuneUndo {
	Disciplina disMod;
	RepoAbstract& rep;
	int oreVechi;
public:
	UndoModificare(RepoAbstract& rep, const  Disciplina& d, int ore) :rep{ rep }, disMod{ d }, oreVechi{ ore } {}
	void doUndo() override {
		rep.modDis(disMod.getDenumire(), oreVechi);
	}
};
