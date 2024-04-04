#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab_1011.h"

class lab_1011 : public QMainWindow
{
    Q_OBJECT

public:
    lab_1011(QWidget *parent = nullptr);
    ~lab_1011();

private:
    Ui::lab_1011Class ui;
};
