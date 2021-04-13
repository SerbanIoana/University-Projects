#pragma once
#include "tape.h"
#include <vector>
#include <iostream>
using namespace std;

class Repository
{
private:
	vector<Tape> tapes;
	vector<Tape>::iterator tapes_iterator;
public:
	/*
		Default constructor
		Initializes an object of type repository
	*/
	Repository() {}

	void add_tape(const Tape& tape);

	void update_tape(Tape& tape, int position);

	void delete_tape(const std::string& title, int position);

	int get_size();

	int get_position_tape(Tape& tape);

	//Tape get_next();

	vector<Tape> get_tapes() const;
};

class AgentRepository
{
private:
	vector<Tape> agent_tapes;
public:
	AgentRepository() {}

	void agent_add_tape(Tape& tape);

	vector<Tape> get_agent_tapes() const;
};