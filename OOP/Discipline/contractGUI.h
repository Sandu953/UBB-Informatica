#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QEvent>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "facultate.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QRegion>
#include <QPainter>
#include <QLayout>
#include <cstdlib>
#include <cmath>
using std::to_string;
using std::set;
using std::vector;

class contractGUI : public QWidget, public Observer {
private:
	QBrush bgBrush;
	Facultate& srv;
	QHBoxLayout* lyMain;
	QListWidget* disList;

	QLabel* lblDenumire;
	QLabel* lblOre;
	QLabel* lblTip;
	QLabel* lblCadru;
	QLineEdit* editDenumire;
	QLineEdit* editOre;
	QLineEdit* editTip;
	QLineEdit* editCadru;

	QPushButton* btnAdd;
	QPushButton* btnGenerate;
	QPushButton* btnEmpty;
	QPushButton* btnExport;
	QPushButton* btnClose;
	QPushButton* btnLabelWindow;
	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;


	QLineEdit* editNoSlider;
	QLabel* lblSlider;
	QSlider* sliderGenerate;

	void initGUI();
	void connectSignalsSlots();

	void reload();
	void add();

	void update() override {
		reload();
	}

public:
	contractGUI(Facultate& Facultate) : srv{ Facultate } {
		initGUI();

		connectSignalsSlots();
	}

};
class contractGUILabel :public QWidget, public Observer {
private:
	Contract& c;
	QLabel* lblNoDis;
	QLineEdit* editNoDis;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		lblNoDis = new QLabel{ "Numar de discipline:" };
		editNoDis = new QLineEdit{};
		ly->addWidget(lblNoDis);
		ly->addWidget(editNoDis);
		setAttribute(Qt::WA_DeleteOnClose);
		c.addObserver(this);
	};
	void update() override {
		this->editNoDis->setText(QString::number(c.allContract().size()));
	};
	~contractGUILabel() {
		c.removeObserver(this);
	}

public:
	contractGUILabel(Contract& contract) :c{ contract } {
		initGUI();
	};

};

class contractGUIDraw :public QWidget, public Observer {
private:
	Contract& contract;
	void paintEvent(QPaintEvent* ve) override {
		QPainter p{ this };
		int a = 200;
		int b = 200;
		int r = 100;
		for (auto dis : contract.allContract()) {
			
			/*x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("favicon.jpg");

			p.drawImage(target, image, source);*/
			//p.drawLine(x, y, width(), height());
			//p.drawImage(x, 0, QImage("favicon.jpg"));

			int t = rand() % 360 + 1;
			//x += 40;
			int x = a + r * sin(t);
			int y = b + r * cos(t);
			//p.drawImage(x, y, QImage("favicon.jpg"));
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("favicon.jpg");

			p.drawImage(target, image, source);

		}
	}

	void initGUI() {
		contract.addObserver(this); 
		//paintEvent(nullptr);
		//update();
		QWidget::update();
	}

	
	~contractGUIDraw() {
		contract.removeObserver(this);
	}

public:
	contractGUIDraw(Contract& contract) :contract{ contract } {
		//initGUI();
		contract.addObserver(this);
		//update();
	
	};
	void update() override {
		repaint();
	};

};
