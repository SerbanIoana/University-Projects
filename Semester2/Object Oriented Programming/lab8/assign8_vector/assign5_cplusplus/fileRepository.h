#pragma once
#include "tape.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class FileRepository
{
private:
	string path;
	vector<Tape>::iterator tapes_iterator;
	vector<Tape> load_tapes();
	void save_tapes(vector<Tape> tapes);

public:
	FileRepository() {}
	void add_tape(Tape& tape);
	void update_tape(Tape& tape);
	void delete_tape(const string& title);
	vector<Tape> get_tapes();
	void set_file_location(string& path);

	Tape get_on_position(int position);
	Tape search_by_title(std::string title);
	int get_size();
};