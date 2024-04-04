#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <Qfont>
#include "disciplina.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Disciplina> disc;
public:
	MyTableModel(const std::vector<Disciplina>& disc) :disc{ disc } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return disc.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::ForegroundRole) {
			auto dis = this->disc[index.row()];
			
		}
		
		

		if (role == Qt::DisplayRole) {

			Disciplina p = disc[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getDenumire());
			}
			else if (index.column() == 1) {
				return QString::number(p.getOre());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getTip());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.getCadru());
			}
		}

		return QVariant{};
	}

	void setDisc(const vector<Disciplina> disc) {
		this->disc = disc;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Denumire");
				case 1:
					return tr("Ore");
				case 2:
					return tr("Tip");
				case 3:
					return tr("Cadru");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};

