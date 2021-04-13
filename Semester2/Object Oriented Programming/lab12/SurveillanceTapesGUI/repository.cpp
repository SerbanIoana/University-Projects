#include "repository.h"
#include "tape.h"
#include <stdexcept>

void Repository::add_tape(Tape& tape)
{
	this->tapes.push_back(tape);
}

void Repository::update_tape(Tape& new_tape)
{
	for (auto& tape : this->tapes)
	{
		if (tape.get_title() == new_tape.get_title())
			tape = new_tape;;
	}
}

void Repository::delete_tape(const std::string& title)
{
	for (int i = 0; i < this->tapes.size(); ++i)
	{
		if (this->tapes[i].get_title() == title)
		{
			this->tapes.erase(this->tapes.begin() + i);
		}
	}
}

Tape Repository::search_by_title(std::string title)
{
	for (const auto& tape : this->tapes)
		if (tape.get_title() == title)
			return tape;
	Tape tape;
	return tape;
}

Tape Repository::get_on_position(int position)
{
	return this->tapes[position];
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

vector<Tape> Repository::get_tapes()
{ 
	return this->tapes; 
}



void AgentRepository::agent_add_tape(Tape& tape)
{
	vector<Tape> agent_tapes = this->load_file();
	agent_tapes.push_back(tape);
	this->save_file(agent_tapes);
}

vector<Tape> AgentRepository::get_agent_tapes() 
{ 
	vector<Tape> agent_tapes = this->load_file();
	return agent_tapes;
}

void AgentRepository::set_mylist_location(string path)
{
	this->path = path;
}

void AgentRepository::open_file()
{
	system(this->path.c_str());
}

