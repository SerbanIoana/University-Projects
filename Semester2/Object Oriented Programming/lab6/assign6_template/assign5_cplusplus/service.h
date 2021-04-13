#pragma once
#include "repository.h"

class Service
{
private:
	Repository repo;
	AgentRepository agent_repo;

public:
	Service(Repository& repository) : repo{ repository }{}

	Repository get_repository() const
	{
		return repo;
	}

	int service_add_tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview);
	int service_update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview);
	int service_delete_tape(const std::string& title);

	Tape service_get_position(int position);

	DynamicVector<Tape> service_get_all() const;

	Tape service_get_next();
	int service_save_tape(std::string& title);

	DynamicVector<Tape> service_get_allAgent() const;

};