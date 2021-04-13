#pragma once
#include "tape.h"
#include "generalRepository.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

class AgentRepository
{
protected:
	string path;
public:
	AgentRepository() {}

	void agent_add_tape(Tape& tape);
	vector<Tape> get_agent_tapes();

	void set_mylist_location(string path);

	virtual void save_file(vector<Tape> tapes) {};
	virtual vector<Tape> load_file() { return vector<Tape>(); };

	void open_file();
};


class Repository : public GeneralRepository
{
private:
	vector<Tape> tapes;
	//vector<Tape>::iterator tapes_iterator;
public:
	Repository() {}

	void add_tape(Tape& tape) override;
	void update_tape(Tape& new_tape) override;
	void delete_tape(const std::string& title) override;
	Tape search_by_title(std::string title) override;
	Tape get_on_position(int position) override;
	vector<Tape> get_tapes() override;
	int get_size() override;

	int get_position_tape(Tape& tape);
};
