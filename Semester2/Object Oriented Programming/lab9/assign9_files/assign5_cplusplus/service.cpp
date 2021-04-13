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
		this->repo->add_tape(tape);
		return 1;
	}
	else
		throw Exception("Tape already exists!");
}

int Service::update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview)
{
	int position = this->search_tape_by_title(title);
	if (position != -1)
	{
		Tape tape{ title, new_filmedAt, new_creationDate, new_accessCount, new_footagePreview };
		this->repo->update_tape(tape);
		return 1;
	}
	else
		throw Exception("Tape doesn't exist!");
}

int Service::delete_tape(const std::string& title)
{
	int position = this->search_tape_by_title(title);
	if (position != -1)
	{
		this->repo->delete_tape(title);
		return 1;
	}
	else
		throw Exception("Tape doesn't exist!");
}

Tape Service::get_on_position(int position)
{
	return this->repo->get_on_position(position);
}

vector<Tape> Service::get_filtered_by_filmedAt(string filmedAt, int accessCount)
{
	vector<Tape> tapes = this->get_admin_tapes();
	vector<Tape> filtered_tapes;
	
	copy_if(tapes.begin(), tapes.end(), std::back_inserter(filtered_tapes), [filmedAt, accessCount](Tape& element)
		{return (element.get_filmedAt() == filmedAt && element.get_accessCount() < accessCount);  });
	
	return filtered_tapes;
}

vector<Tape> Service::get_admin_tapes()
{
	return this->repo->get_tapes();
}

/*
GeneralRepository Service::get_repository() const
{
	return repo;
}*/

Tape Service::next_tape()
{
	Tape next_tape;
	if (step_iterator == 0 || step_iterator == this->repo->get_size())
	{
		step_iterator = 0;
		next_tape = this->get_on_position(step_iterator);
		step_iterator++;
	}
	else if (step_iterator != this->repo->get_size())
	{
		next_tape = this->get_on_position(step_iterator);
		step_iterator++;
	}
	return next_tape;
}

int Service::save_tape(const string& title)
{
	Tape tape = this->repo->search_by_title(title);
	if (tape.get_title() != "Null")
	{
		this->agent_repo->add_tape(tape);
		return 1;
	}
	else
		throw Exception("Tape doesn't exist!");
}

vector<Tape> Service::get_agent_tapes()
{
	return this->agent_repo->get_tapes();
}

void Service::file_location(string path)
{
	this->repo = new FileRepository{};
	((FileRepository*)this->repo)->set_file_location(path);
}

void Service::mylist_location(string path)
{
	string extension = path.substr(path.size() - 4);
	if (extension == ".csv")
	{
		this->agent_repo = new CSVRepo{};
	}
	else if (extension == "html")
	{
		this->agent_repo = new HTMLRepo{};
	}
	((FileRepository*)this->agent_repo)->set_file_location(path);
}

void Service::open_mylist()
{
	((FileRepository*)this->agent_repo)->open_file();
}

