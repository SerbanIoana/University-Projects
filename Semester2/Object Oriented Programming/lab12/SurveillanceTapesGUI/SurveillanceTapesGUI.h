#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SurveillanceTapesGUI.h"
#include "service.h"

class SurveillanceTapesGUI : public QMainWindow
{
    Q_OBJECT

public:
    SurveillanceTapesGUI(Service& _service, QWidget *parent = Q_NULLPTR);

private:
    Service& service;
    Ui::SurveillanceTapesGUIClass ui;

    void populate_list();
    void populate_agent_list();

    void add_tape();
    void update_tape();
    void delete_tape();
    void filter_tapes();

    void next_tape();
    void save_tape();

    void mylist_open();
    void set_fileLocation();
    void set_mylistLocation();

    void connect_signals_slots();
    int get_selected_index() const;
};
