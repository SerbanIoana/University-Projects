#include "ui.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <exception>

using namespace std;

void Ui::print_menu()
{
	cout << endl << "You are in mode A" << endl;
	cout << "add title, filmedAt, creationDate, accessCount, footagePreview" << endl;
	cout << "update title, newFilmedAt, newCreationDate, newAccessCount, newFootagePreview" << endl;
	cout << "delete title" << endl;
	cout << "list" << endl;
	cout << "exit" << endl;
	cout << endl;
}

void Ui::print_agent_menu()
{
	cout << endl << "You are in mode B" << endl;
	cout << "next" << endl;
	cout << "save title" << endl;
	cout << "list filmedAt, accessCount" << endl;
	cout << "mylist" << endl;
	cout << "exit" << endl;
	cout << endl;
}

Date Ui::format_creationDate(const std::string& input_date)
{
	int day, month, year;
	char* char_date = new char[input_date.length() + 1];
	char* token;
	std::strcpy(char_date, input_date.c_str());

	token = strtok(char_date, "-");
	day = atoi(token);
	char_date = strtok(NULL, "-");
	month = atoi(char_date);
	char_date = strtok(NULL, "-");
	year = atoi(char_date);

	Date date{ day, month, year };
	return date;
}

void Ui::ui_add_tape(char* arguments)
{
	string title, filmedAt, footagePreview, input_date, input_accessCount;
	Date creationDate;
	int accessCount;

	arguments = strtok(NULL, ",");
	title = arguments;
	arguments = strtok(NULL, ",");
	filmedAt = arguments;
	filmedAt = filmedAt.substr(1);
	arguments = strtok(NULL, ",");
	input_date = arguments;
	input_date = input_date.substr(1);

	arguments = strtok(NULL, ",");
	input_accessCount = arguments;
	input_accessCount = input_accessCount.substr(1);
	accessCount = stoi(input_accessCount);

	arguments = strtok(NULL, ",");
	footagePreview = arguments;
	footagePreview = footagePreview.substr(1);

	creationDate = this->format_creationDate(input_date);

	int result = this->service.service_add_tape(title, filmedAt, creationDate, accessCount, footagePreview);
	if (result == 0)
		throw exception();
}

void Ui::ui_update_tape(char* arguments)
{
	string title, new_filmedAt, new_footagePreview, input_date, input_accessCount;
	Date new_creationDate;
	int new_accessCount;

	arguments = strtok(NULL, ",");
	title = arguments;
	arguments = strtok(NULL, ",");
	new_filmedAt = arguments;
	new_filmedAt = new_filmedAt.substr(1);
	arguments = strtok(NULL, ",");
	input_date = arguments;
	input_date = input_date.substr(1);

	arguments = strtok(NULL, ",");
	input_accessCount = arguments;
	input_accessCount = input_accessCount.substr(1);
	new_accessCount = stoi(input_accessCount);

	arguments = strtok(NULL, ",");
	new_footagePreview = arguments;
	new_footagePreview = new_footagePreview.substr(1);

	new_creationDate = this->format_creationDate(input_date);

	int result = this->service.service_update_tape(title, new_filmedAt, new_creationDate, new_accessCount, new_footagePreview);
	if (result == 0)
		throw exception();
}

void Ui::ui_delete_tape(char* arguments)
{
	string title;
	arguments = strtok(NULL, ",");
	title = arguments;

	int result = this->service.service_delete_tape(title);
	if (result == 0)
		throw exception();
}

void Ui::ui_list()
{
	DynamicVector<Tape> tapes = this->service.service_get_all();
	for (int i = 0; i < tapes.get_size(); i++)
	{
		Tape tape = tapes.get_position(i);
		cout << tape.print_tape() << endl;
	}
}

void Ui::admin_mode()
{
	while (true)
	{
		print_menu();
		string input;
		char* command, token;
		cout << "Give command: ";
		getline(cin, input);

		if (input == "mode B")
			agent_mode();
		else
		{
			char* user_input = new char[input.length() + 1];
			std::strcpy(user_input, input.c_str());
			command = strtok(user_input, " ");

			if (strcmp(command, "exit") == 0)
				exit(0);
			else if (strcmp(command, "add") == 0)
			{
				try
				{
					this->ui_add_tape(user_input);
				}
				catch (exception& e)
				{
					cout << "Tape already exists!\n";
				}
			}
			else if (strcmp(command, "update") == 0)
			{
				try
				{
					this->ui_update_tape(user_input);
				}
				catch (exception& e)
				{
					cout << "Tape doesn't exist!\n";
				}
			}
			else if (strcmp(command, "delete") == 0)
			{
				try
				{
					this->ui_delete_tape(user_input);
				}
				catch (exception& e)
				{
					cout << "Tape doesn't exist!\n";
				}
			}
			else if (strcmp(command, "list") == 0)
				this->ui_list();
			else
				cout << "Invalid command!" << endl;
		}
	}
}

void Ui::ui_next()
{
	Tape tape = service.service_get_next();
	cout << tape.print_tape() << endl;
}

void Ui::ui_save_tape(char* arguments)
{
	string title;
	arguments = strtok(NULL, ",");
	title = arguments;

	int result = this->service.service_save_tape(title);
	if (result == 0)
		throw exception();
}

void Ui::ui_list_filmedAt(char* arguments)
{
	string filmedAt, input_accessCount;
	int accessCount;

	arguments = strtok(NULL, ",");
	filmedAt = arguments;
	
	arguments = strtok(NULL, ",");
	input_accessCount = arguments;
	input_accessCount = input_accessCount.substr(1);
	accessCount = stoi(input_accessCount);
	
	
	DynamicVector<Tape> tapes = service.service_get_all();
	for (int i = 0; i < tapes.get_size(); ++i)
	{
		if (tapes[i].get_filmedAt() == filmedAt)
		{
			if (tapes[i].get_accessCount() < accessCount)
			{
				cout << tapes[i].print_tape() << endl;
			}
		}
	}
}

void Ui::ui_my_list()
{
	DynamicVector<Tape> agent_tapes = service.service_get_allAgent();
	for (int i = 0; i < agent_tapes.get_size(); ++i)
	{
		cout << agent_tapes[i].print_tape() << endl;
	}
}

void Ui::agent_mode()
{
	while (true)
	{
		print_agent_menu();
		string input;
		char* command, token;
		cout << "Give command: ";
		getline(cin, input);

		if (input == "mode A")
			admin_mode();
		else
		{
			char* user_input = new char[input.length() + 1];
			std::strcpy(user_input, input.c_str());
			command = strtok(user_input, " ");

			if (strcmp(command, "exit") == 0)
				exit(0);
			else if (strcmp(command, "next") == 0)
			{
				this->ui_next();
			}
			else if (strcmp(command, "save") == 0)
			{
				try
				{
					this->ui_save_tape(user_input);
				}
				catch (exception& e)
				{
					cout << "Tape doesn't exist!\n";
				}
			}
			else if (strcmp(command, "list") == 0)
			{
				this->ui_list_filmedAt(user_input);
			}
			else if (strcmp(command, "mylist") == 0)
			{
				this->ui_my_list();
			}
			else
				cout << "Invalid command!" << endl;
		}		
	}
}


void Ui::run()
{
	//print_menu();
	string mode;
	cout << "Give mode: ";
	getline(cin, mode);
	if (mode == "mode A")
	{
		admin_mode();
	}
	else if (mode == "mode B")
	{
		agent_mode();
	}
	else if (mode == "exit")
	{
		exit(0);
	}
	else
		cout << "Wrong mode!\n";
}