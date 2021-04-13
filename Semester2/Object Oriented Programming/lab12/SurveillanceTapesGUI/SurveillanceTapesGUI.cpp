#include "SurveillanceTapesGUI.h"
#include <qmessagebox.h>

using namespace std;

SurveillanceTapesGUI::SurveillanceTapesGUI(Service& _service, QWidget *parent)
    : QMainWindow(parent), service{_service}
{
    ui.setupUi(this);
	//this->service.mylist_location("file2.html");
    this->populate_list();
	this->connect_signals_slots();
}

void SurveillanceTapesGUI::populate_list()
{
    this->ui.tapesListWidget->clear();

    vector<Tape> admin_tapes = this->service.get_admin_tapes();

    for (Tape& tape : admin_tapes)
        this->ui.tapesListWidget->addItem(QString::fromStdString(tape.print_tape()));
}

void SurveillanceTapesGUI::populate_agent_list()
{
	this->ui.agentListWidget->clear();

	vector<Tape> agent_tapes = this->service.get_agent_tapes();

	for (Tape& tape : agent_tapes)
		this->ui.agentListWidget->addItem(QString::fromStdString(tape.print_tape()));
}

void SurveillanceTapesGUI::add_tape()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string filmedAt = this->ui.filmedAtLineEdit->text().toStdString();
	string input_creationDate = this->ui.creationDateLineEdit->text().toStdString();
	Date creationDate = creationDate.tokenize_date(input_creationDate);
	int accessCount = this->ui.accessCountLineEdit->text().toInt();
	string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();

	if (title == "" || filmedAt == "" || input_creationDate == "" || accessCount == 0 || footagePreview == "")
	{
		QMessageBox::critical(this, "Error", "Give all of the arguments!");
		return;
	}

	this->service.add_tape(title, filmedAt, creationDate, accessCount, footagePreview);
	this->populate_list();
}

void SurveillanceTapesGUI::update_tape()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string filmedAt = this->ui.filmedAtLineEdit->text().toStdString();
	string input_creationDate = this->ui.creationDateLineEdit->text().toStdString();
	Date creationDate = creationDate.tokenize_date(input_creationDate);
	int accessCount = this->ui.accessCountLineEdit->text().toInt();
	string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();

	if (title == "" || filmedAt == "" || input_creationDate == "" || accessCount == 0 || footagePreview == "")
	{
		QMessageBox::critical(this, "Error", "Give all of the arguments!");
		return;
	}

	this->service.update_tape(title, filmedAt, creationDate, accessCount, footagePreview);
	this->populate_list();
}

void SurveillanceTapesGUI::delete_tape()
{
	int selectedIndex = this->get_selected_index();

	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No item selected!");
		return;
	}

	Tape tape = this->service.get_admin_tapes()[selectedIndex];
	this->service.delete_tape(tape.get_title());
	this->populate_list();
}

void SurveillanceTapesGUI::filter_tapes()
{
	string filmedAt = this->ui.filter_filmedAtLineEdit->text().toStdString();
	int accessCount = this->ui.filter_accessCountLineEdit->text().toInt();

	if (filmedAt == "" || accessCount == 0)
	{
		QMessageBox::critical(this, "Error", "No arguments given!");
		return;
	}

	vector<Tape> filtered_tapes = this->service.get_filtered_by_filmedAt(filmedAt, accessCount);

	this->ui.filterListWidget->clear();

	for (Tape& tape : filtered_tapes)
		this->ui.filterListWidget->addItem(QString::fromStdString(tape.print_tape()));
}

void SurveillanceTapesGUI::next_tape()
{
	this->ui.nextLineEdit->clear();
	Tape tape = this->service.next_tape();
	this->ui.nextLineEdit->setText(QString::fromStdString(tape.print_tape()));
}

void SurveillanceTapesGUI::save_tape()
{
	int selectedIndex = this->get_selected_index();

	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No item selected!");
		return;
	}

	Tape tape = this->service.get_admin_tapes()[selectedIndex];
	this->service.save_tape(tape.get_title());
	this->populate_agent_list();
}

void SurveillanceTapesGUI::mylist_open()
{
	this->service.open_mylist();
}

void SurveillanceTapesGUI::set_fileLocation()
{
	string path = this->ui.fileLocationLineEdit->text().toStdString();

	if (path == "")
	{
		QMessageBox::critical(this, "Error", "No path given!");
		return;
	}

	this->service.file_location(path);
	this->populate_list();
}

void SurveillanceTapesGUI::set_mylistLocation()
{
	string path = this->ui.mylistLineEdit->text().toStdString();

	if (path == "")
	{
		QMessageBox::critical(this, "Error", "No path given!");
		return;
	}

	this->service.mylist_location(path);
	this->populate_agent_list();
}

int SurveillanceTapesGUI::get_selected_index() const
{
	QModelIndexList selectedIndexes = this->ui.tapesListWidget->selectionModel()->selectedIndexes();

	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.filmedAtLineEdit->clear();
		this->ui.creationDateLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void SurveillanceTapesGUI::connect_signals_slots()
{
	QObject::connect(this->ui.tapesListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->get_selected_index();

		if (selectedIndex < 0)
			return;
		Tape tape = this->service.get_admin_tapes()[selectedIndex];
		this->ui.titleLineEdit->setText(QString::fromStdString(tape.get_title()));
		this->ui.filmedAtLineEdit->setText(QString::fromStdString(tape.get_filmedAt()));
		this->ui.creationDateLineEdit->setText(QString::fromStdString(tape.get_creationDate().print_date()));
		this->ui.accessCountLineEdit->setText(QString::fromStdString(to_string(tape.get_accessCount())));
		this->ui.footagePreviewLineEdit->setText(QString::fromStdString(tape.get_footagePreview()));
		});

	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::add_tape);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::delete_tape);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::update_tape);
	QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::filter_tapes);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::next_tape);
	QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::save_tape);
	QObject::connect(this->ui.mylistButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::mylist_open);
	QObject::connect(this->ui.fileLocationButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::set_fileLocation);
	QObject::connect(this->ui.mylistLocationButton, &QPushButton::clicked, this, &SurveillanceTapesGUI::set_mylistLocation);
}
