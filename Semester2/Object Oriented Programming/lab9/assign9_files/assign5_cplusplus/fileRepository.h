#pragma once
#include "tape.h"
#include "generalRepository.h"
#include "validator.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class FileRepository : public GeneralRepository
{
protected:
	string path;
	//vector<Tape>::iterator tapes_iterator;
	virtual vector<Tape> load_tapes();
	virtual void save_tapes(vector<Tape> tapes);

	TapeValidator validator;

public:
	FileRepository() {}

	void add_tape(Tape& tape) override;
	void update_tape(Tape& new_tape) override;
	void delete_tape(const string& title) override;
	Tape search_by_title(std::string title) override;
	Tape get_on_position(int position) override;
	vector<Tape> get_tapes() override;
	int get_size() override;

	void set_file_location(string& path);
	void open_file();
};



class CSVRepo : public FileRepository
{
protected:
	void save_tapes(std::vector<Tape> tapes) override;
	vector<Tape> load_tapes() override;
	//void open_file();
};

class HTMLRepo : public FileRepository
{
protected :
	void save_tapes(vector<Tape> tapes) override;
	vector<Tape> load_tapes() override;
	//void open_file();
};
