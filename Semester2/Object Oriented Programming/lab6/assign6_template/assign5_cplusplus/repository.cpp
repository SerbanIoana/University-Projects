#include "repository.h"
#include "tape.h"
#include <stdexcept>

int Repository::add_tape(const Tape& tape)
{
	int position = this->search_tape(tape.get_title());
	if (position != -1)
		return 0;
	else
	{
		this->tapes.add(tape);
		return 1;
	}
}

int Repository::update_tape(Tape& tape)
{
	int position = this->search_tape(tape.get_title());
	if (position == -1)
		return 0;
	else
	{
		this->tapes.update(position, tape);
		return 1;
	}
}

int Repository::delete_tape(const std::string& title)
{
	int position = this->search_tape(title);
	if (position == -1)
		return 0;
	else
	{
		this->tapes.remove(position);
		return 1;
	}
}

int Repository::search_tape(const std::string& title)
{
	for (int i = 0; i < this->tapes.get_size(); ++i)
	{
		if (title == this->get_tapes().get_position(i).get_title())
			return i;
	}
	return -1;
}

Tape Repository::get_position_tape(int position)
{
	return this->tapes.get_position(position);
}

int Repository::get_sizeRepository()
{
	return this->tapes.get_size();
}

Tape Repository::get_next()
{
	Tape next_tape;
	if (this->tapes_iterator == NULL || this->tapes_iterator == this->tapes.end())
	{
		this->tapes_iterator = this->tapes.begin();
		next_tape = *(this->tapes_iterator);
		this->tapes_iterator++;
	}
	else if (this->tapes_iterator != this->tapes.end())
	{
		next_tape = *(this->tapes_iterator);
		this->tapes_iterator++;
	}

	return next_tape;
}

DynamicVector<Tape> Repository::get_tapes() const 
{ 
	return tapes; 
}

void AgentRepository::agent_add_tape(Tape tape)
{
	agent_tapes.add(tape);
}

DynamicVector<Tape> AgentRepository::get_agent_tapes() const 
{ 
	return agent_tapes; 
}
