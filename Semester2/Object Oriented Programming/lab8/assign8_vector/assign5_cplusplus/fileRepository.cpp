#include "fileRepository.h"

vector<Tape> FileRepository::load_tapes()
{
	ifstream file{ this->path };
	vector<Tape> tapes;
	Tape tape;
	while (file >> tape)
		tapes.push_back(tape);
	file.close();
	return tapes;
}

void FileRepository::save_tapes(vector<Tape> tapes)
{
	ofstream file{ this->path };
	for (const auto& tape : tapes)
		file << tape;
	file.close();
}

void FileRepository::add_tape(Tape& tape)
{
	vector<Tape> tapes = this->load_tapes();
	tapes.push_back(tape);
	this->save_tapes(tapes);
}

void FileRepository::update_tape(Tape& new_tape)
{
	vector<Tape> tapes = this->load_tapes();
	for (auto& tape : tapes)
	{
		if (tape.get_title() == new_tape.get_title())
			tape = new_tape;;
	}
	this->save_tapes(tapes);
}

void FileRepository::delete_tape(const string& title)
{
	vector<Tape> tapes = load_tapes();
	for (int i = 0; i < tapes.size(); ++i)
	{
		if (tapes[i].get_title() == title)
		{
			tapes.erase(tapes.begin() + i);
		}
	}
	this->save_tapes(tapes);
}

vector<Tape> FileRepository::get_tapes()
{
	vector<Tape> tapes = this->load_tapes();
	return tapes;
}

void FileRepository::set_file_location(string& path)
{
	this->path = path;
}

Tape FileRepository::get_on_position(int position)
{
	vector<Tape> tapes = this->load_tapes();
	return tapes[position];
}

Tape FileRepository::search_by_title(std::string title)
{
	vector<Tape> tapes = this->load_tapes();
	for (const auto& tape : tapes)
		if (tape.get_title() == title)
			return tape;
	Tape tape;
	return tape;
}

int FileRepository::get_size()
{
	vector<Tape> tapes = this->load_tapes();
	return tapes.size();
}
