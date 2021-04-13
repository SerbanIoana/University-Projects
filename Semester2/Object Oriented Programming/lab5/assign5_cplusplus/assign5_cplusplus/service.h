#pragma once
#include "repository.h"

class Service
{
private:
	Repository& repo;

public:
	Service(Repository& repo) : repo{ repo } {}

	Repository& get_repository() const
	{
		return repo;
	}

	int service_add_tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview);
	int service_update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview);
	int service_delete_tape(const std::string& title);

	DynamicVector service_get_all() const
	{
		return this->repo.get_tapes();
	}

};