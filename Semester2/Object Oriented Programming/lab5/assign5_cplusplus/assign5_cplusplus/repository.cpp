#include "repository.h"

int Repository::add_tape(const Tape& tape)
{
	return this->tapes.add(tape);
}

int Repository::update_tape(Tape& tape)
{
	return this->tapes.update(tape);
}

int Repository::delete_tape(const std::string& title)
{
	return this->tapes.remove(title);
}

int Repository::search_tape(const std::string& title)
{
	return this->tapes.search(title);
}

TElem Repository::get_position(int position)
{
	return this->tapes.get_position(position);
}

int Repository::get_sizeRepository()
{
	return this->tapes.get_size();
}