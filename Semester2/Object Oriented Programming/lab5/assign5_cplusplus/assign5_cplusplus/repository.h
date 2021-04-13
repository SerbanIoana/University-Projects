#pragma once
#include "tape.h"
#include "dynamicVector.h"

class Repository
{
private:
	DynamicVector tapes;
public:
	/*
		Default constructor
		Initializes an object of type repository
	*/
	Repository() {}

	int add_tape(const Tape& tape);

	int update_tape(Tape& tape);

	int delete_tape(const std::string& title);

	int search_tape(const std::string& title);

	int get_sizeRepository();

	TElem get_position(int position);

	DynamicVector get_tapes() const { return tapes; }
};