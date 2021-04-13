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

Tape::Tape() : title(""), filmedAt(""), creationDate(Date()), accessCount(0), footagePreview("") {}

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
