#pragma once

#include "repo.h"

typedef struct {
	Repository* repo;
}Service;

Service* create_service(Repository* repo);
int add_map_service(Service* service, int mapCatalogueNumber, char stateOfDeterioration[], char mapType[], int yearsOfStorage);
int delete_map_service(Service* service, int mapCatalogueNumber);
int update_map_service(Service* service, int mapCatalogueNumber, char new_stateOfDeterioration[], char new_mapType[], int new_yearsOfStorage);
Map* getMaps_lessThan_yearsOfStorage(Service* service, int* numberOfMaps, int maxYearsOfStorage);
Map* order_by_stateOfDeterioration(Service* service, Map* maps, int lenght);
char* get_map_arguments(Service* service, int mapCatalogueNumber);
Repository* get_repo(Service* service);
Container get_all(Service* service);
