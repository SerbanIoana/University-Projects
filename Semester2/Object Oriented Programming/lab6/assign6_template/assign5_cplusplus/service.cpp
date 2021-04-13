#include "service.h"

int Service::service_add_tape(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int accessCount, const std::string& footagePreview)
{
	Tape tape{ title, filmedAt, creationDate, accessCount, footagePreview };
	return this->repo.add_tape(tape);
}

int Service::service_update_tape(const std::string& title, const std::string& new_filmedAt, const Date& new_creationDate, const int new_accessCount, const std::string& new_footagePreview)
{
	Tape tape{ title, new_filmedAt, new_creationDate, new_accessCount, new_footagePreview };
	return this->repo.update_tape(tape);
}

int Service::service_delete_tape(const std::string& title)
{
	return this->repo.delete_tape(title);
}

Tape Service::service_get_position(int position)
{
	return this->repo.get_position_tape(position);
}

DynamicVector<Tape> Service::service_get_all() const
{
	return this->repo.get_tapes();
}

Tape Service::service_get_next()
{
	return repo.get_next();
}

int Service::service_save_tape(std::string & title)
{
	int position = this->repo.search_tape(title);
	if (position == -1)
		return 0;
	else
	{
		Tape tape = this->repo.get_position_tape(position);
		agent_repo.agent_add_tape(tape);
		return 1;
	}
}

DynamicVector<Tape> Service::service_get_allAgent() const
{
	return this->agent_repo.get_agent_tapes();
}

