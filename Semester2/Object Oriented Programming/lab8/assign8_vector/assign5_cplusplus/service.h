#pragma once
#include "repository.h"
#include "fileRepository.h"

class Service
{
private:
	FileRepository repo;
	AgentRepository agent_repo;
	int step_iterator = 0;

public:
	Service(FileRepository& repository) : repo{ repository }{}

	FileRepository get_repository() const;

	int search_tape_by_title(const string& title);
	int add_tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview);
	int update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview);
	int delete_tape(const std::string& title);

	Tape get_on_position(int position);
	vector<Tape> get_filtered_by_filmedAt(string filmedAt, int accessCount);
	vector<Tape> get_admin_tapes();

	Tape next_tape();
	int save_tape(const string& title);
	vector<Tape> get_agent_tapes() const;

	void file_location(string path);

};