#include "appConfig.h"

void AppConfigurator::read_file()
{
	ifstream file{ this->path };
	getline(file, this->repository_type);
	//file >> this->repository_type;
}

GeneralRepository* AppConfigurator::create_admin_repository()
{
	if (this->repository_type == "inmemory")
	{
		Repository* new_repo = new Repository();
		return new_repo;
	}
	else if (this->repository_type == "file based")
	{
		FileRepository* new_repo = new FileRepository("tapes.txt");
		return new_repo;
	}
}

GeneralRepository* AppConfigurator::create_agent_repository()
{
	if (this->repository_type == "inmemory")
	{
		Repository* new_repo = new Repository();
		return new_repo;
	}
	else if (this->repository_type == "file based")
	{
		FileRepository* new_repo = new FileRepository();
		//string file = "file2.html";
		//new_repo->set_file_location(file);
		return new_repo;
	}
}
