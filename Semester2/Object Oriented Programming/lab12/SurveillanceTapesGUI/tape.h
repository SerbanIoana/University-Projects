#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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
	int get_year() const { return year; }

	std::string print_date();
	Date tokenize_date(const string& input_date);

	friend bool operator==(const Date& date1, const Date& date2);
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

	vector<string> tokenize_tape(const string& line, char separator);

	friend istream& operator>>(istream& input_file, Tape& tape);
	friend ostream& operator<<(ostream& output_file, const Tape& tape);

	friend bool operator==(const Tape& tape1, const Tape& tape2);

	string HTML_format();
};
