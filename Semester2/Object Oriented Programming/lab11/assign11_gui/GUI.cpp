#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>

GUI::GUI(Service& _service) : service{ _service }
{
	this->initialize_GUI();
	this->populate_list();
	this->connect_signals_slots();
}

void GUI::initialize_GUI()
{
	this->tapesListWidget = new QListWidget{};
	this->titleLineEdit = new QLineEdit{};
	this->filmedAtLineEdit = new QLineEdit{};
	this->creationDateLineEdit = new QLineEdit{};
	this->accessCountLineEdit = new QLineEdit{};
	this->footagePreviewLineEdit = new QLineEdit{};

	QVBoxLayout* mainLayout = new QVBoxLayout{ this };
	mainLayout->addWidget(this->tapesListWidget);

	QFormLayout* tapeDetailsLayout = new QFormLayout{};
	tapeDetailsLayout->addRow("Title", this->titleLineEdit);
	tapeDetailsLayout->addRow("Filmed At", this->filmedAtLineEdit);
	tapeDetailsLayout->addRow("Creation Date", this->creationDateLineEdit);
	tapeDetailsLayout->addRow("Access Count", this->accessCountLineEdit);
	tapeDetailsLayout->addRow("Footage Preview", this->footagePreviewLineEdit);

	mainLayout->addLayout(tapeDetailsLayout);
}

void GUI::populate_list()
{
	this->tapesListWidget->clear();

	vector<Tape> allTapes = this->service.get_admin_tapes();

	for (Tape& tape : allTapes)
		this->tapesListWidget->addItem(QString::fromStdString(tape.print_tape()));
}

int GUI::get_selected_index() const
{
	QModelIndexList selectedIndexes = this->tapesListWidget->selectionModel()->selectedIndexes();

	if (selectedIndexes.size() == 0)
	{
		this->titleLineEdit->clear();
		this->filmedAtLineEdit->clear();
		this->creationDateLineEdit->clear();
		this->accessCountLineEdit->clear();
		this->footagePreviewLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void GUI::connect_signals_slots()
{
	QObject::connect(this->tapesListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->get_selected_index();

		if (selectedIndex < 0)
			return;
		Tape tape = this->service.get_admin_tapes()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(tape.get_title()));
		this->filmedAtLineEdit->setText(QString::fromStdString(tape.get_filmedAt()));
		this->creationDateLineEdit->setText(QString::fromStdString(tape.get_creationDate().print_date()));
		this->accessCountLineEdit->setText(QString::fromStdString(to_string(tape.get_accessCount())));
		this->footagePreviewLineEdit->setText(QString::fromStdString(tape.get_footagePreview()));

		});
}


