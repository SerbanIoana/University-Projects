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
	validator.validate_tape(tape);
	vector<Tape> tapes = this->load_tapes();
	tapes.push_back(tape);
	this->save_tapes(tapes);
}

void FileRepository::update_tape(Tape& new_tape)
{
	validator.validate_tape(new_tape);
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

void FileRepository::open_file()
{
	system(this->path.c_str());
}



void CSVRepo::save_tapes(std::vector<Tape> tapes)
{
	ofstream file{ this->path };
	for (const auto& tape : tapes)
		file << tape;
	file.close();
}

vector<Tape> CSVRepo::load_tapes()
{
	ifstream file{ this->path };
	vector<Tape> tapes;
	Tape tape;
	while (file >> tape)
		tapes.push_back(tape);
	file.close();
	return tapes;
}

void HTMLRepo::save_tapes(vector<Tape> tapes)
{
	ofstream file{ this->path };
	file << "<!DOCTYPE html>\n<html>\n<head>\n";
	file << "<title>SAVED TAPES</title>\n";
	file << "</head>\n<body style=\"background-color:#FF69B4;\">\n<table border=\"1\"\n";

	file << "<tr>\n<td><b>Title</td></b>\n<td><b>FilmedAt</td></b>\n<td><b>CreationDate</td></b>\n<td><b>AccessCount</td></b>\n<td><b>FootagePreview</td></b>\n</tr>\n";

	for (auto tape : tapes)
		file << tape.HTML_format() << endl;

	file << "</table>\n</body>\n</html>";
	file.close();
}

vector<Tape> HTMLRepo::load_tapes()
{
	vector<Tape> tapes;
	string line;
	ifstream file{ this->path };
	string title, filmedAt, input_creationDate, input_accessCount, footagePreview;
	Date creationDate;
	int accessCount;

	for (int i = 0; i <= 13; i++)
		getline(file, line);

	getline(file, line); //<tr>
	while (line == "<tr>")
	{
		getline(file, line);
		title = line.substr(4, line.size() - 9);

		getline(file, line);
		filmedAt = line.substr(4, line.size() - 9);

		getline(file, line);
		input_creationDate = line.substr(4, line.size() - 9);
		creationDate = creationDate.tokenize_date(input_creationDate);

		getline(file, line);
		input_accessCount = line.substr(4, line.size() - 9);
		accessCount = stoi(input_accessCount);

		getline(file, line);
		footagePreview = line.substr(4, line.size() - 9);

		Tape tape{ title, filmedAt, creationDate, accessCount, footagePreview };
		tapes.push_back(tape);

		getline(file, line); //</tr>
		getline(file, line); //<tr>
	}
	file.close();
	return tapes;
}
