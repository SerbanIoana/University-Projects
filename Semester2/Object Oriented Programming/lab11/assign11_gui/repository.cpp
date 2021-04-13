#include "repository.h"
#include "tape.h"
#include <stdexcept>

void Repository::add_tape(const Tape& tape)
{
	this->tapes.push_back(tape);
}

void Repository::update_tape(Tape& tape, int position)
{
	this->tapes[position] = tape;
}

void Repository::delete_tape(const std::string& title, int position)
{
	this->tapes.erase(this->tapes.begin() + position);
}

int Repository::get_position_tape(Tape& tape)
{
	int size = tapes.size();
	for (int i = 0; i < size; ++i)
		if (tape.get_title() == tapes[i].get_title())
			return i;
	return -1;
}

int Repository::get_size()
{
	return this->tapes.size();
}

vector<Tape> Repository::get_tapes() const 
{ 
	return this->tapes; 
}

void AgentRepository::agent_add_tape(Tape& tape)
{
	agent_tapes.push_back(tape);
}

vector<Tape> AgentRepository::get_agent_tapes() const 
{ 
	return this->agent_tapes; 
}
