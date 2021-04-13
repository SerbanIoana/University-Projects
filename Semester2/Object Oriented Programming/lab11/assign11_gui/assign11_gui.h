#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_assign11_gui.h"

class assign11_gui : public QMainWindow
{
    Q_OBJECT

public:
    assign11_gui(QWidget *parent = Q_NULLPTR);

private:
    Ui::assign11_guiClass ui;
};
