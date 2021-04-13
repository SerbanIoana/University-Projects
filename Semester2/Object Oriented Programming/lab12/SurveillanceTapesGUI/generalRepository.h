#pragma once
#include "tape.h"

class GeneralRepository
{
public:
	GeneralRepository() {}

	virtual void add_tape(Tape& tape) = 0;
	virtual void update_tape(Tape& new_tape) = 0;
	virtual void delete_tape(const std::string& title) = 0;
	virtual Tape search_by_title(std::string title) = 0;
	virtual Tape get_on_position(int position) = 0;
	virtual vector<Tape> get_tapes() = 0;
	virtual int get_size() = 0;
};
