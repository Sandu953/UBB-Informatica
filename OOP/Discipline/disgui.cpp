#include "disgui.h"
#include "disciplina.h"
#include "facultate.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <string>
#include <algorithm>
#include <QCheckBox>

void DisGUI::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub 3 butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	/*lst = new QListWidget;
	vl->addWidget(lst);*/

	/*QTableView* tbl2 = new QTableView;
	tbl2 = new QTableView;
	tbl2->columnWidth(4);*/
	/*tbl = new QTableWidget;
	tbl->setColumnCount(4);
	QStringList header;
	header  << "Denumire" << "Ore" << "Tip" << "Cadru";
	QHeaderView* head;*/

	
	
	/*tbl->setHorizontalHeaderLabels(header);

	vl->addWidget(tbl);*/
	vl->addWidget(tableDis);

	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByDenumire = new QPushButton("Sort by Denumire");
	lyBtnsDr->addWidget(btnSortByDenumire);

	btnSortByOre = new QPushButton("Sort by ore");
	lyBtnsDr->addWidget(btnSortByOre);

	btnSortByCadruTip = new QPushButton("Sort by cadru si tip");
	lyBtnsDr->addWidget(btnSortByCadruTip);

	btnAfiseaza = new QPushButton("Afiseaza discipline");
	lyBtnsDr->addWidget(btnAfiseaza);

	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtDenumire = new QLineEdit;
	formLDetalii->addRow(new QLabel("Denumire:"), txtDenumire);
	txtOre = new QLineEdit;
	formLDetalii->addRow(new QLabel("Ore:"), txtOre);
	txtTip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), txtTip);
	txtCadru = new QLineEdit;
	formLDetalii->addRow(new QLabel("Cadru:"), txtCadru);
	txtUtil = new QLineEdit;
	formLDetalii->addRow(new QLabel("Auxiliar:"), txtUtil);

	btnAdd = new QPushButton("Add disciplina");
	formLDetalii->addWidget(btnAdd);

	btnDelete = new QPushButton("Sterge disciplina");
	formLDetalii->addWidget(btnDelete);

	btnModify = new QPushButton("Modifica disciplina");
	formLDetalii->addWidget(btnModify);

	btnCauta = new QPushButton("Cauta disciplina");
	formLDetalii->addWidget(btnCauta);

	btnFilterByOre = new QPushButton("Filtreaza dupa ore");
	formLDetalii->addWidget(btnFilterByOre);

	btnFilterByCadru = new QPushButton("Filtreaza dupa cadru");
	formLDetalii->addWidget(btnFilterByCadru);

	btnUndo = new QPushButton("Undo");
	formLDetalii->addWidget(btnUndo);

	/*btnExportCos = new QPushButton("Export CVS");
	formLDetalii->addWidget(btnExportCos);

	formLDetalii->addWidget(addtobag);

	btnRandomCos = new QPushButton("Adauga random in contract");
	formLDetalii->addWidget(btnRandomCos);*/

	btnContract = new QPushButton{ "Contract" };
	formLDetalii->addWidget(btnContract);

	//for (auto& d : ctr.tipunic()) {
	//	
	//	f1 = new QFrame();
	//	a = new QPushButton();
	//	a->setText(QString::fromStdString(d));
	//	formLDetalii->addWidget(a);
	//}

	/*butoane_tip = new QWidget;
	QFormLayout* formLDetalii2 = new QFormLayout;
	butoane_tip->setLayout(formLDetalii2);*/

	ly->addWidget(widDetalii);

	butoane_tip->setLayout(layout);
	ly->addWidget(butoane_tip);

	
}


void DisGUI::update_tip() {
	/*clearLayout(layout);
	for (auto& d : ctr.tipunic()) {
		QPushButton* a = new QPushButton(QString::fromStdString(d));
		layout->addWidget(a);
		int nr = ctr.nrtip(d);
		QObject::connect(a, &QPushButton::clicked, [nr]() {
			QMessageBox::information(nullptr, "Numar discipline", QString::number(nr));
			});
	}*/
}
//
//void clearLayout(QLayout* layout) {
//	if (layout == NULL)
//		return;
//	QLayoutItem* item;
//	while ((item = layout->takeAt(0))) {
//		if (item->layout()) {
//			clearLayout(item->layout());
//			delete item->layout();
//		}
//		if (item->widget()) {
//			delete item->widget();
//		}
//		delete item;
//	}
//}


void DisGUI::bag_init()
{
	auto mainlybag = new QVBoxLayout;
	mainlybag->addWidget(coslist);

	//titlu_bag->setPlaceholderText(QString::fromStdString("Titlu"));
	//autor_bag->setPlaceholderText(QString::fromStdString("Autor"));
	//gen_bag->setPlaceholderText(QString::fromStdString("Gen"));
	//an_bag->setPlaceholderText(QString::fromStdString("An"));
	QWidget* widDetalii2 = new QWidget;
	QFormLayout* formLDetalii2 = new QFormLayout;
	widDetalii2->setLayout(formLDetalii2);
	denumire_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Denumire:"), denumire_bag);
	ore_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Ore:"), ore_bag);
	tip_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Tip:"), tip_bag);
	cadru_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Cadru:"), cadru_bag);

	auto secondbagly = new QVBoxLayout;
	secondbagly->addLayout(form);
	mainlybag->addWidget(golestebag);
	mainlybag->addLayout(secondbagly);
	mainlybag->addWidget(widDetalii2);
	cos->setLayout(mainlybag);
	load_data_to_bag();
}

void DisGUI::load_data_to_bag()
{
	coslist->clear();
	for (const auto elem : ctr.allContract())
	{
		auto item = new QListWidgetItem(QString::fromStdString(elem.getDenumire()));
		coslist->addItem(item);
	}
}


void DisGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByDenumire, &QPushButton::clicked, [&]() {
		//reloadList(ctr.sortByDenumire());
		reloadTable(ctr.sortByDenumire());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByOre, &QPushButton::clicked, [&]() {
		//reloadList(ctr.sortByOre());
		reloadTable(ctr.sortByOre());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByCadruTip, &QPushButton::clicked, [&]() {
		//reloadList(ctr.sortByCadruTip());
		reloadTable(ctr.sortByCadruTip());
		});
	//cand se selecteaza elementul din lista incarc detaliile
	//QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
	//	if (lst->selectedItems().isEmpty()) {
	//		//nu este nimic selectat (golesc detaliile)
	//		txtDenumire->setText("");
	//		txtOre->setText("");
	//		txtTip->setText("");
	//		txtCadru->setText("");
	//		return;
	//	}

	//	QListWidgetItem* selItem = lst->selectedItems().at(0);
	//	selItem->font().setBold(true);
	//	selItem->setCheckState(Qt::CheckState::Checked);
	//	QString denumire = selItem->text();
	//	txtDenumire->setText(denumire);

	//	try {
	//
	//		Disciplina d = ctr.rep.find(denumire.toStdString());
	//	    txtOre->setText(QString::number(d.getOre()));

	//		txtTip->setText(QString::fromStdString(d.getTip()));
	//		
	//		txtCadru->setText(QString::fromStdString(d.getCadru()));
	//	
	//	}
	//	catch (DisRepoException& ex) {
	//		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	//	}
	//	catch (ValidateException& ex) {
	//		string m;
	//		for (auto s : ex.getMsg()) {
	//			m.append(s);
	//		}
	//		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(m));
	//	}
	//	
	//	});



	QObject::connect(btnAdd, &QPushButton::clicked, this, &DisGUI::addNewDis);
	QObject::connect(btnDelete, &QPushButton::clicked, this, &DisGUI::deleteDis);
	QObject::connect(btnModify, &QPushButton::clicked, this, &DisGUI::modDis);
	QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
		try {

			vector<Disciplina> fnd;
			fnd.push_back(ctr.rep.find(txtUtil->text().toStdString()));
			//reloadList(fnd);
			reloadTable(fnd);
		}
		catch (DisRepoException& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (ValidateException& ex) {
			string m;
			for (auto s : ex.getMsg()) {
				m.append(s);
			}
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(m));
		}
		});
	QObject::connect(btnFilterByCadru, &QPushButton::clicked, [&]() {
		//reloadList(ctr.filtrareCadru(txtUtil->text().toStdString()));
		reloadTable(ctr.filtrareCadru(txtUtil->text().toStdString()));
		});
	QObject::connect(btnAfiseaza, &QPushButton::clicked, [&]() {
		//reloadList(ctr.getAll());
		reloadTable(ctr.getAll());
		});
	QObject::connect(btnFilterByOre, &QPushButton::clicked, [&]() {
		//reloadList(ctr.filtrareOreMaiMulte(txtUtil->text().toInt()));
		reloadTable(ctr.filtrareOreMaiMulte(txtUtil->text().toInt()));
		});
	QObject::connect(btnUndo, &QPushButton::clicked, this, &DisGUI::undo);

	QObject::connect(btnContract, &QPushButton::clicked, [&]() {
		conGUI.show();
		});

	//QObject::connect(addtobag, &QPushButton::clicked, [&]() {
	//	add_to_bag();
	//	cos->show();
	//	});

	//QObject::connect(btnExportCos, &QPushButton::clicked, [&]() {
	//	exportCVS();
	//	
	//	});

	//QObject::connect(golestebag, &QPushButton::clicked, [&]() {
	//	ctr.golesteContract();
	//	load_data_to_bag();
	//	cos->show();
	//	});

	//QObject::connect(btnRandomCos, &QPushButton::clicked, [&]() {
	//	randomBag();
	//	cos->show();
	//	});

	////pwntru afisare
	//QObject::connect(coslist, &QListWidget::itemSelectionChanged, [&]() {
	//	if (coslist->selectedItems().isEmpty()) {
	//		//nu este nimic selectat (golesc detaliile)
	//		denumire_bag->setText("");
	//		ore_bag->setText("");
	//		tip_bag->setText("");
	//		cadru_bag->setText("");
	//		return;
	//	}
	//	QListWidgetItem* selItem = coslist->selectedItems().at(0);
	//	QString denumire = selItem->text();
	//	denumire_bag->setText(denumire);

	//	try {

	//		Disciplina d = ctr.rep.find(denumire.toStdString());
	//		ore_bag->setText(QString::number(d.getOre()));

	//		tip_bag->setText(QString::fromStdString(d.getTip()));

	//		cadru_bag->setText(QString::fromStdString(d.getCadru()));

	//	}
	//	catch (DisRepoException& ex) {
	//		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	//	}
	//	catch (ValidateException& ex) {
	//		string m;
	//		for (auto s : ex.getMsg()) {
	//			m.append(s);
	//		}
	//		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(m));
	//	}

	//	});
}

void DisGUI::addNewDis() {
	try {
		ctr.addDis(txtDenumire->text().toStdString(),  txtOre->text().toInt(),txtTip->text().toStdString(), txtCadru->text().toStdString());
		//reloadList(ctr.getAll());
		reloadTable(ctr.getAll());
		update_tip();
	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		string m;
		for (auto s : ex.getMsg()) {
			m.append(s);
		}
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(m));
	}
}

void DisGUI::deleteDis() {
	try {
		ctr.stergeDis(txtDenumire->text().toStdString());
		//reloadList(ctr.getAll());
		reloadTable(ctr.getAll());
		update_tip();

	}
	catch (ValidateException& ex) {
		string m;
		for (auto s : ex.getMsg()) {
			m.append(s);
		}
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(m));
	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void DisGUI::modDis() {
	try {
		ctr.modifica(txtDenumire->text().toStdString(), txtOre->text().toInt());
		//reloadList(ctr.getAll());
		reloadTable(ctr.getAll());
	}
	catch (ValidateException& ex) {
		string m;
		for (auto s : ex.getMsg()) {
			m.append(s);
		}
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(m));
	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void DisGUI::undo() {
	try {
		ctr.undo();
		//reloadList(ctr.getAll());
		reloadTable(ctr.getAll());
		update_tip();
	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	}

}

void DisGUI::add_to_bag() {
	try {
		ctr.adaugaLaContract(txtDenumire->text().toStdString());
		load_data_to_bag();
	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void DisGUI::randomBag() {
	try {
		ctr.adaugaRandom(txtUtil->text().toInt());
		load_data_to_bag();
	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void DisGUI::exportCVS() {
	try {
		ctr.exportContractCVS(txtUtil->text().toStdString());

	}
	catch (DisRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void DisGUI::reloadTable(vector<Disciplina> disc) {
	model->setDisc(ctr.getAll());
}

void DisGUI::reloadList(const std::vector<Disciplina>& disc) {
	//lst->clear();
	//for (const auto& d : disc) {
	//	QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.getDenumire()));
	//	if (item->checkState() == Qt::Checked)
	//		item->setFont(QFont{ "Italic",20 });
	//	lst->addItem(item);
	//	//adaug in lista (invizibil) si type 
	//	//if (std::find(colorize.cbegin(), colorize.cend(), p) !=colorize.end()){//merge pt ca am adaugat operator== la Pet		
	//		//item->setBackground(QBrush{ QColor{Qt::red},Qt::CrossPattern });		
	//		//item->setBackgroundColor(QColor{ Qt::red });
	//	//}
	//}

	
	tbl->setRowCount(disc.size());
	int nr = 0;
	for (const auto& d : disc) {
		/*tbl->setItem(nr,0, new QTableWidgetItem(QCheckBox()));*/
		tbl->setItem(nr,0, new QTableWidgetItem(QString::fromStdString(d.getDenumire())));
		tbl->setItem(nr, 1, new QTableWidgetItem(QString::number(d.getOre())));
		tbl->setItem(nr, 2, new QTableWidgetItem(QString::fromStdString(d.getTip())));
		tbl->setItem(nr, 3, new QTableWidgetItem(QString::fromStdString(d.getCadru())));
		nr += 1;
		//	QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(d.getDenumire()),QString::number(d.getOre()), QString::fromStdString(d.getTip()), QString::fromStdString(d.getCadru()), tbl);
		//	adaug in lista (invizibil) si type 
		//	if (std::find(colorize.cbegin(), colorize.cend(), p) !=colorize.end()){//merge pt ca am adaugat operator== la Pet		
		//		item->setBackground(QBrush{ QColor{Qt::red},Qt::CrossPattern });		
		//		item->setBackgroundColor(QColor{ Qt::red });
		//	}
	}
}
