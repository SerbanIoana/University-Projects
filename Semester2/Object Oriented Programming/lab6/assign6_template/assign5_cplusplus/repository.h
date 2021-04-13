#pragma once
#include "tape.h"
#include "dynamicVector.h"

class Repository
{
private:
	DynamicVector<Tape> tapes;
	DynamicVector<Tape>::iterator tapes_iterator;
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

	Tape get_position_tape(int position);

	Tape get_next();

	DynamicVector<Tape> get_tapes() const;
};

class AgentRepository
{
private:
	DynamicVector<Tape> agent_tapes;
public:
	AgentRepository() {}

	void agent_add_tape(Tape tape);

	DynamicVector<Tape> get_agent_tapes() const;
};