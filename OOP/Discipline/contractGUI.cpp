#include "contractGUI.h"


void contractGUI::initGUI() {
	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};

	lblDenumire = new QLabel{ "Denumire" };
	/*lblOre = new QLabel{ "Ore" };
	lblTip = new QLabel{ "Tip" };
	lblCadru = new QLabel{ "Cadru" };*/
	editDenumire = new QLineEdit{};
	/*editOre = new QLineEdit{};
	editTip = new QLineEdit{};
	editCadru = new QLineEdit{};*/

	lblSlider = new QLabel{ "Nr. discipline de generat" };
	editNoSlider = new QLineEdit{};
	lyEdits->addRow(lblDenumire, editDenumire);
	/*lyEdits->addRow(lblOre, editOre);
	lyEdits->addRow(lblTip, editTip);
	lyEdits->addRow(lblCadru, editCadru);*/
	lyEdits->addRow(lblSlider, editNoSlider);
	formW->setLayout(lyEdits);


	btnAdd = new QPushButton{ "Adauga in contract" };
	btnGenerate = new QPushButton{ "Genereaza random" };
	btnEmpty = new QPushButton{ "Goleste" };
	btnExport = new QPushButton{ "Export cvs" };
	btnClose = new QPushButton{ "Close" };

	btnLabelWindow = new QPushButton{ "Fereastra numar discipline" };
	//btnLabelWindow->setStyleSheet("background-color: cyan");

	/*btnTableWindow = new QPushButton{ "Fereastra playlist tabel" };
	btnTableWindow->setStyleSheet("background-color: magenta");*/

	btnDrawWindow = new QPushButton{ "Fereastra desen" };
	//btnDrawWindow->setStyleSheet("background-color: yellow");


	/*sliderGenerate = new QSlider{};
	sliderGenerate->setMinimum(1);
	sliderGenerate->setMaximum(srv.getAll().size());*/

	lyLeft->addWidget(formW);
	lyLeft->addWidget(btnAdd);
	lyLeft->addWidget(btnGenerate);
	lyLeft->addWidget(btnEmpty);
	lyLeft->addWidget(btnExport);
	lyLeft->addWidget(btnClose);
	lyLeft->addWidget(btnLabelWindow);
	//lyLeft->addWidget(btnTableWindow);
	lyLeft->addWidget(btnDrawWindow);

	QWidget* rightSide = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	rightSide->setLayout(lyRight);

	disList = new QListWidget{};
	disList->setFixedWidth(320);
	bgBrush = QBrush();

	disList->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(disList);


	lyMain->addWidget(leftSide);
	//lyMain->addWidget(sliderGenerate);
	lyMain->addWidget(rightSide);


}

void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void contractGUI::connectSignalsSlots() {
	srv.getContract().addObserver(this);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &contractGUI::add);
	/*QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});*/
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		//int noDis = this->sliderGenerate->value();
		int noDis = editNoSlider->text().toInt();
	//	editNoSlider->setText(QString::number(noDis));
		qDebug() << "Au fost adaugate " << noDis<<" discipline";
		int howManyAdded = srv.adaugaRandom(noDis);
		this->reload();
		});
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
		srv.golesteContract();
		this->reload();
		});
	QObject::connect(btnExport, &QPushButton::clicked, [&]() {

		});
	QObject::connect(btnClose, &QPushButton::clicked, this, &contractGUI::close);

	QObject::connect(btnLabelWindow, &QPushButton::clicked, this, [&]() {
		auto labelWindow = new contractGUILabel{ srv.getContract() };
		labelWindow->show();
		});
	/*QObject::connect(btnTableWindow, &QPushButton::clicked, this, [&]() {
		auto tableWindow = new contractGUITable{ srv.getContract() };
		tableWindow->show();
		});*/

	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new contractGUIDraw{ srv.getContract() };
		
		drawWindow->show();
		//drawWindow->update();
		});

	QObject::connect(disList, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = disList->selectedItems();
		for (int i = 0; i < disList->count(); ++i)
		{
			QListWidgetItem* item = disList->item(i);
			item->setBackground(bgBrush);
		}
		for (auto item : selItms) {
			qDebug() << item->text();
			//item->setBackground(Qt::green); // sets green background
		}

		});




}


void contractGUI::reload() {

	this->disList->clear();

	const vector<Disciplina>& dis = srv.allContract();
	for (auto& d : dis) {
		QString currentItem = QString::fromStdString(d.getDenumire() + "\t" + to_string(d.getOre()) + "\t" + d.getTip() + "\t" + d.getCadru());
		this->disList->addItem(currentItem);
	}


}

void contractGUI::add() {
	try {
		string denumire = editDenumire->text().toStdString();
		/*int ore = editOre->text().toInt();
		string tip = editTip->text().toStdString();
		string cadru = editCadru->text().toStdString();*/

		editDenumire->clear();
		/*editOre->clear();
		editTip->clear();
		editCadru->clear();*/

		this->srv.adaugaLaContract(denumire);
		this->reload();

		//afisam un mesaj pentru a anunta utilizatorul ca disciplina s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina adaugata cu succes."));

	}
	catch (DisRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
	catch (ValidateException& ve) {
		string msg;
		for (auto m : ve.getMsg()) {
			msg += m;
			msg += "\n";
		}
		QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
	}

}
//void contractGUI::add() {
//	try {
//		string titlu = editTitlu->text().toStdString();
//		string artist = editArtist->text().toStdString();
//
//		editTitlu->clear();
//		editArtist->clear();
//
//
//		this->srv.addToPlaylist(titlu, artist);
//		this->reloadPlaylist();
//
//		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
//		QMessageBox::information(this, "Info", QString::fromStdString("Melodie adaugata cu succes."));
//
//	}
//	catch (RepoException& re) {
//		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
//	}
//	catch (ValidationException& ve) {
//		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
//	}
//
//}


