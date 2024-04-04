#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QTableView>
#include <QTableWidget>
#include <qboxlayout.h>
#include <QFormLayout>
#include "facultate.h"
#include "disciplina.h"
#include <vector>
#include <qlabel.h>
#include "contractGUI.h"
#include "MyModel.h"

//class SmallGUI : public QWidget {
//private:
//	QLabel* lbl = new QLabel("Nimic");
//public:
//	SmallGUI() {
//		QHBoxLayout* ly = new QHBoxLayout;
//		setLayout(ly);
//		ly->addWidget(lbl);
//	}
//
//	void setDis(const Disciplina& d) {
//		lbl->setText(QString{ d.getDenumire().c_str()});
//	}
//
//};

class DisGUI : public QWidget {
private:
	Facultate& ctr;
	contractGUI conGUI{ctr};
	QListWidget* lst;
	QTableWidget* tbl;

	MyTableModel* model;

	QTableView* tableDis = new QTableView;

	QPushButton* btnSortByDenumire;
	QPushButton* btnSortByOre;
	QPushButton* btnSortByCadruTip;
	QLineEdit* txtDenumire;
	QLineEdit* txtOre;
	QLineEdit* txtTip;
	QLineEdit* txtCadru;
	QLineEdit* txtUtil;

	QPushButton* btnAdd;
	QPushButton* btnDelete;
	QPushButton* btnModify;
	QPushButton* btnCauta;
	QPushButton* btnFilterByCadru;
	QPushButton* btnFilterByOre;
	QPushButton* btnAfiseaza;
	QPushButton* btnUndo;
	QPushButton* btnAddCos;
	QPushButton* btnEmptyCos;
	QPushButton* btnRandomCos;
	QPushButton* btnRandomCos2;
	QPushButton* btnExportCos;
	//QPushButton* btnExportCos;
	QPushButton* a;
	QFrame* f1;

	QPushButton* addtobag = new QPushButton{ "Adauga in cos" };
	QWidget* cos = new QWidget;
	QPushButton* golestebag = new QPushButton{ "Goleste cosul" };
	//QPushButton* randombag = new QPushButton{ "Genereaza cos random" };
	QFormLayout* form = new QFormLayout;
	QListWidget* coslist = new QListWidget;
	QLineEdit* denumire_bag = new QLineEdit;
	QLineEdit* ore_bag = new QLineEdit;
	QLineEdit* tip_bag = new QLineEdit;
	QLineEdit* cadru_bag = new QLineEdit;

	QWidget* butoane_tip = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout;

	QPushButton* btnContract;

	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Disciplina>& disc);
	void addNewDis();
	void deleteDis();
	void modDis();
	void filterByOre();
	void filterByCadru();
	void bag_init();
	void add_to_bag();
	void randomBag();
	void load_data_to_bag();
	void initFereastraCos();
	void exportCVS();
	void undo();
	void update_tip();
	void reloadTable(vector<Disciplina> disc);

public:
	DisGUI(Facultate& ctr) :ctr{ ctr } {
		initGUICmps();
		this->model = new MyTableModel{ ctr.getAll()};
		this->tableDis->setModel(model);
		//update_tip();
		connectSignalsSlots();
		reloadTable(ctr.getAll());
		//reloadList(ctr.getAll());
		//bag_init();
		//load_data_to_bag();
	}

};

void clearLayout(QLayout* layout);