#include "ui.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <exception>

using namespace std;



void Ui::print_directions()
{
	cout << endl;
	cout << "First you should choose the fileLocation, mylistLocation and then the mode!" << endl;
	cout << "fileLocation path (ex: 'fileLocation E:\\DOCUMENTE\\FACULTA\\SEM2\\oop\\lab\\9')" << endl;
	cout << "mylistLocation path (ex: 'mylistLocation E:\\DOCUMENTE\\FACULTA\\SEM2\\oop\\lab\\9')" << endl;
	cout << "mode X (ex: 'mode A')" << endl;
}

void Ui::print_menu()
{
	cout << endl << "You are in mode A" << endl;
	cout << "add title, filmedAt, creationDate, accessCount, footagePreview" << endl;
	cout << "update title, newFilmedAt, newCreationDate, newAccessCount, newFootagePreview" << endl;
	cout << "delete title" << endl;
	cout << "list" << endl;
	cout << "fileLocation path" << endl;
	cout << "mylistLocation path" << endl;
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
	cout << "mylistLocation path" << endl;
	cout << "exit" << endl;
	cout << endl;
}

void Ui::add_tape_data(char* arguments)
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

	creationDate = creationDate.tokenize_date(input_date);

	int result = this->service.add_tape(title, filmedAt, creationDate, accessCount, footagePreview);
}

void Ui::update_tape_data(char* arguments)
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

	new_creationDate = new_creationDate.tokenize_date(input_date);

	int result = this->service.update_tape(title, new_filmedAt, new_creationDate, new_accessCount, new_footagePreview);
}

void Ui::delete_tape_data(char* arguments)
{
	string title;
	arguments = strtok(NULL, ",");
	title = arguments;

	int result = this->service.delete_tape(title);
}

void Ui::list()
{
	vector<Tape> tapes = this->service.get_admin_tapes();
	for (auto tape : tapes)
	{
		cout << tape.print_tape() << endl;
	}
}

void Ui::admin_mode()
{
	while (true)
	{
		print_menu();
		string input;
		string command;

		cout << "Give command: ";
		getline(cin, input);

		if (input == "mode B")
			agent_mode();
		else
		{
			char* user_input = new char[input.length() + 1];
			std::strcpy(user_input, input.c_str());
			command = strtok(user_input, " ");

			try
			{
				if (command.compare("exit") == 0)
					exit(0);
				else if (command.compare("add") == 0)
				{
						this->add_tape_data(user_input);
				}
				else if (command.compare("update") == 0)
				{
						this->update_tape_data(user_input);
				}
				else if (command.compare("delete") == 0)
				{
						this->delete_tape_data(user_input);
				}
				else if (command.compare("list") == 0)
					this->list();
				else if (command.compare("fileLocation") == 0)
				{
					string path = input.substr(input.find(" ") + 1);
					this->file_location_data(path);
				}
				else if (command.compare("mylistLocation") == 0)
				{
					string path = input.substr(input.find(" ") + 1);
					this->mylist_location_data(path);
				}
				else
					cout << "Invalid command!" << endl;
			}
			catch(Exception& exception_message)
			{
				cout << exception_message.get_message();
			}
			
		}
	}
}

void Ui::next_tape_data()
{
	Tape tape = service.next_tape();
	cout << tape.print_tape() << endl;
}

void Ui::save_tape_data(char* arguments)
{
	string title;
	arguments = strtok(NULL, ",");
	title = arguments;

	int result = this->service.save_tape(title);
	if (result == 0)
		throw exception();
}

void Ui::list_filmedAt(char* arguments)
{
	string filmedAt, input_accessCount;
	int accessCount;

	arguments = strtok(NULL, ",");
	filmedAt = arguments;
	
	arguments = strtok(NULL, ",");
	input_accessCount = arguments;
	input_accessCount = input_accessCount.substr(1);
	accessCount = stoi(input_accessCount);
	
	vector<Tape> filtered_tapes = this->service.get_filtered_by_filmedAt(filmedAt, accessCount);
	for (auto tape : filtered_tapes)
		cout << tape.print_tape() << endl;
}

void Ui::my_list()
{
	/*
	vector<Tape> agent_tapes = service.get_agent_tapes();
	for (auto tape : agent_tapes)
	{
		cout << tape.print_tape() << endl;
	}
	*/

	this->service.open_mylist();
}

void Ui::file_location_data(string arguments)
{
	this->service.file_location(arguments);
}

void Ui::mylist_location_data(string arguments)
{
	this->service.mylist_location(arguments);
}

void Ui::agent_mode()
{
	while (true)
	{
		print_agent_menu();
		string input;
		string command;

		cout << "Give command: ";
		getline(cin, input);

		if (input == "mode A")
			admin_mode();
		else
		{
			char* user_input = new char[input.length() + 1];
			std::strcpy(user_input, input.c_str());
			command = strtok(user_input, " ");

			try
			{
				if (command.compare("exit") == 0)
					exit(0);
				else if (command.compare("next") == 0)
				{
					this->next_tape_data();
				}
				else if (command.compare("save") == 0)
				{
						this->save_tape_data(user_input);
				}
				else if (command.compare("list") == 0)
				{
					this->list_filmedAt(user_input);
				}
				else if (command.compare("mylist") == 0)
				{
					this->my_list();
				}
				else if (command.compare("fileLocation") == 0)
				{
					string path = input.substr(input.find(" ") + 1);
					this->file_location_data(path);
				}
				else if (command.compare("mylistLocation") == 0)
				{
					string path = input.substr(input.find(" ") + 1);
					this->mylist_location_data(path);
				}
				else
					cout << "Invalid command!" << endl;
			}
			catch (Exception& exception_message)
			{
				cout << exception_message.get_message();
			}
			
		}		
	}
}


void Ui::run()
{
	print_directions();
	string command, input;
	
	while (true)
	{
		cout << "Give mode, fileLocation, mylistLocation: " << endl;
		getline(cin, input);
		command = input.substr(0, input.find(" "));

		if (command.compare("exit") == 0)
			exit(0);
		else if (command.compare("mode") == 0)
		{
			if (input == "mode A")
			{
				admin_mode();
			}
			else if (input == "mode B")
			{
				agent_mode();
			}
			else
				cout << "Wrong mode!" << endl;
		}
		else if (command.compare("fileLocation") == 0)
		{
			string path = input.substr(input.find(" ") + 1);
			this->file_location_data(path);
		}
		else if (command.compare("mylistLocation") == 0)
		{
			string path = input.substr(input.find(" ") + 1);
			this->mylist_location_data(path);
		}
		else
			cout << "Invalid command!" << endl;
	}
}