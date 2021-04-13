#include "tape.h"
#include <iostream>
#include <string>

using namespace std;

std::string Date::print_date()
{
	string date_print;
	if (day <= 9)
		date_print = "0";
	date_print += std::to_string(this->day) + "-";
	if (month <= 9)
		date_print += "0";
	date_print += std::to_string(this->month) + "-" + std::to_string(this->year);
	return date_print;
}

Date Date::tokenize_date(const string & input_date)
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

bool operator==(const Date & date1, const Date & date2)
{
	return
	{
		date1.get_day() == date2.get_day() &&
		date1.get_month() == date2.get_month() &&
		date1.get_year() == date2.get_year()
	};
}

Tape::Tape() : title("Null"), filmedAt(""), creationDate(Date()), accessCount(0), footagePreview("") {}

//constructor
Tape::Tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview)
{
	this->title = title;
	this->filmedAt = filmedAt;
	this->creationDate = creationDate;
	this->accessCount = accessCount;
	this->footagePreview = footagePreview;
}

std::string Tape::print_tape()
{
	return this->get_title() + " " + this->get_filmedAt() + " " + this->get_creationDate().print_date() + " " + std::to_string(this->get_accessCount()) + " " + this->get_footagePreview();
}

vector<string> Tape::tokenize_tape(const string& line, char separator)
{
	vector<string> arguments;
	stringstream ss(line);
	string token;
	while (getline(ss, token, separator))
		arguments.push_back(token);
	return arguments;
}


istream& operator>>(istream& input_file, Tape& tape)
{
	string line;
	getline(input_file, line);
	vector<string> tokens = tape.tokenize_tape(line, ',');

	if (tokens.size() != 5)
		return input_file;

	tape.title = tokens[0];
	tape.filmedAt = tokens[1];
	Date date = date.tokenize_date(tokens[2]);
	tape.creationDate = date;
	tape.accessCount = stoi(tokens[3]);
	tape.footagePreview = tokens[4];

	return input_file;
}

ostream& operator<<(ostream& output_file, const Tape& tape)
{
	output_file << tape.get_title() << "," << tape.get_filmedAt() << "," << tape.get_creationDate().print_date() << "," << std::to_string(tape.get_accessCount()) << "," << tape.get_footagePreview() << "\n";
	return output_file;
}

bool operator==(const Tape & tape1, const Tape & tape2)
{
	return
	{
		tape1.get_title() == tape2.get_title() &&
		tape1.get_filmedAt() == tape2.get_filmedAt() &&
		tape1.get_creationDate() == tape2.get_creationDate() &&
		tape1.get_accessCount() == tape2.get_accessCount() &&
		tape1.get_footagePreview() == tape2.get_footagePreview()
	};
}
