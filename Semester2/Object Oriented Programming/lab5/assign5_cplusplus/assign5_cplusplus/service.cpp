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