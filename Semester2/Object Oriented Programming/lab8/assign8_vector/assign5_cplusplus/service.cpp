#include "service.h"
#include <algorithm>

int Service::search_tape_by_title(const std::string& title)
{
	vector<Tape> tapes = this->get_admin_tapes();
	int size = tapes.size();
	for (int i = 0; i < size; ++i)
	{
		if (title == tapes[i].get_title())
			return i;
	}
	return -1;
}

int Service::add_tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview)
{
	int position = this->search_tape_by_title(title);
	if (position == -1)
	{
		Tape tape{ title, filmedAt, creationDate, accessCount, footagePreview };
		this->repo.add_tape(tape);
		return 1;
	}
	return 0;
}

int Service::update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview)
{
	int position = this->search_tape_by_title(title);
	if (position != -1)
	{
		Tape tape{ title, new_filmedAt, new_creationDate, new_accessCount, new_footagePreview };
		this->repo.update_tape(tape);
		return 1;
	}
	return 0;
}

int Service::delete_tape(const std::string& title)
{
	int position = this->search_tape_by_title(title);
	if (position != -1)
	{
		this->repo.delete_tape(title);
		return 1;
	}
	return 0;
}

Tape Service::get_on_position(int position)
{
	return this->repo.get_on_position(position);
}

vector<Tape> Service::get_filtered_by_filmedAt(string filmedAt, int accessCount)
{
	vector<Tape> tapes = this->get_admin_tapes();
	vector<Tape> filtered_tapes(tapes.size());

	for (const auto& tape : tapes)
	{
		copy_if(tapes.begin(), tapes.end(), filtered_tapes.begin(), [filmedAt, accessCount](Tape& element)
		{return (element.get_filmedAt() == filmedAt && element.get_accessCount() < accessCount);  });
	}
	filtered_tapes.shrink_to_fit();
	return filtered_tapes;

}

vector<Tape> Service::get_admin_tapes()
{
	return this->repo.get_tapes();
}

FileRepository Service::get_repository() const
{
	return repo;
}

Tape Service::next_tape()
{
	Tape next_tape;
	if (step_iterator == 0 || step_iterator == this->repo.get_size())
	{
		step_iterator = 0;
		next_tape = this->get_on_position(step_iterator);
		step_iterator++;
	}
	else if (step_iterator != this->repo.get_size())
	{
		next_tape = this->get_on_position(step_iterator);
		step_iterator++;
	}
	return next_tape;
}

int Service::save_tape(const string& title)
{
	Tape tape = this->repo.search_by_title(title);
	if (tape.get_title() != "Null")
	{
		this->agent_repo.agent_add_tape(tape);
		return 1;
	}
	return 0;
}

vector<Tape> Service::get_agent_tapes() const
{
	return this->agent_repo.get_agent_tapes();
}

void Service::file_location(string path)
{
	this->repo.set_file_location(path);
}

