#include "service.h"
#include <stdio.h>
#include <stdlib.h>

Service* create_service(Repository* repo)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repo = repo;
	return service;
}

int add_map_service(Service* service, int mapCatalogueNumber, char stateOfDeterioration[], char mapType[], int yearsOfStorage)
{
	Map map = create_map(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
	int result = add_map(service->repo, map);
	return result;
}

int delete_map_service(Service* service, int mapCatalogueNumber)
{
	int result = delete_map(service->repo, mapCatalogueNumber);
	return result;
}

int update_map_service(Service* service, int mapCatalogueNumber, char new_stateOfDeterioration[], char new_mapType[], int new_yearsOfStorage)
{
	Map new_map = create_map(mapCatalogueNumber, new_stateOfDeterioration, new_mapType, new_yearsOfStorage);
	int result = update_map(service->repo, new_map);
	return result;
}

Repository* get_repo(Service* service)
{
	return service->repo;
}

Container get_all(Service* service) 
{
	return get_data(service->repo);
}
