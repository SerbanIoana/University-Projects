#pragma once
#include "repository.h"
#include "fileRepository.h"

class Service
{
private:
	GeneralRepository* repo;
	GeneralRepository* agent_repo;
	int step_iterator = 0;

public:
	Service(GeneralRepository* repository, GeneralRepository* _agent_repo) : repo{ repository }, agent_repo { _agent_repo } {}

	//GeneralRepository get_repository() const;

	int search_tape_by_title(const string& title);
	int add_tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview);
	int update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview);
	int delete_tape(const std::string& title);

	Tape get_on_position(int position);
	vector<Tape> get_filtered_by_filmedAt(string filmedAt, int accessCount);
	vector<Tape> get_admin_tapes();

	Tape next_tape();
	int save_tape(const string& title);
	vector<Tape> get_agent_tapes();

	void file_location(string path);

	void mylist_location(string path);
	void open_mylist();

};