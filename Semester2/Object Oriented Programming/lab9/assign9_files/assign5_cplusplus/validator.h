#pragma once
#include "tape.h"
#include "exception.h"

using namespace std;

class TapeValidator
{
public:
	static string validate_date(const Date& date);
	static void validate_tape(const Tape& tape);
	static void validateTitleForDelete(string& title);
};