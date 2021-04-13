#pragma once
#include <iostream>

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date() : day(0), month(0), year(0) {}
	Date(int day, int month, int year) : day(day), month(month), year(year) {}

	int get_day() const { return day; }
	int get_month() const { return month; }
	int ge_year() const { return year; }

	std::string print_date();
};

class Tape
{
private:
	std::string title;
	std::string filmedAt;
	Date creationDate;
	int accessCount;
	std::string footagePreview;

public:
	//constructor
	Tape();

	Tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview);

	//getters
	std::string get_title() const { return title; }
	std::string get_filmedAt() const { return filmedAt; }
	Date get_creationDate() const { return creationDate; }
	int get_accessCount() const { return accessCount; }
	std::string get_footagePreview() const { return footagePreview; }

	//setters
	void set_filmedAt(std::string& data) { filmedAt = data; }
	void set_creationDate(Date data) { creationDate = data; }
	void set_accessCount(int data)	{ accessCount = data; }
	void set_footagePreview(std::string& data) { footagePreview = data; }

	std::string print_tape();
};
