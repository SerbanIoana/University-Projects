#pragma once
#include <qwidget.h>
#include "service.h"
#include <qlistwidget.h>
#include <qlineedit.h>

class GUI : public QWidget
{
private:
	Service& service;

	//graphical elements
	QListWidget* tapesListWidget;
	QLineEdit* titleLineEdit;
	QLineEdit* filmedAtLineEdit;
	QLineEdit* creationDateLineEdit;
	QLineEdit* accessCountLineEdit;
	QLineEdit* footagePreviewLineEdit;

public:
	GUI(Service& _service);

private:
	void initialize_GUI();
	void populate_list();
	void connect_signals_slots();

	int get_selected_index() const;

};

