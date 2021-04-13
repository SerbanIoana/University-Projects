#pragma once

#include "repo.h"

typedef struct {
	Repository* repo;
}Service;

Service* create_service(Repository* repo);
int add_map_service(Service* service, int mapCatalogueNumber, char stateOfDeterioration[], char mapType[], int yearsOfStorage);
int delete_map_service(Service* service, int mapCatalogueNumber);
int update_map_service(Service* service, int mapCatalogueNumber, char new_stateOfDeterioration[], char new_mapType[], int new_yearsOfStorage);
Repository* get_repo(Service* service);
Container get_all(Service* service);
