#pragma once
#include <iostream>
#include "generalRepository.h"
#include "repository.h"
#include "fileRepository.h"

using namespace std;

class AppConfigurator
{
private:
	string path;
	string repository_type;
public:
	AppConfigurator(string _path) : path{ _path } { this->read_file(); }

	void read_file();
	GeneralRepository* create_admin_repository();
	GeneralRepository* create_agent_repository();
};

