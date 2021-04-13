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

Map* getMaps_lessThan_yearsOfStorage(Service* service, int* numberOfMaps, int maxYearsOfStorage)
{
	Map* maps_lessThan_yearsOfStorage = findMaps_lessThan_yearsOfStorage(service->repo, numberOfMaps, maxYearsOfStorage);
	return order_by_stateOfDeterioration(service, maps_lessThan_yearsOfStorage, *numberOfMaps);
}

Map* order_by_stateOfDeterioration(Service* service, Map* maps, int lenght)
{
	int i, j;
	for (i = 0; i < lenght - 1; i++)
		for (j = i + 1; j < lenght; j++)
			if (strcmp(get_stateOfDeterioration(&maps[i]), get_stateOfDeterioration(&maps[j])) > 0)
			{
				Map copy_map = maps[i];
				maps[i] = maps[j];
				maps[j] = copy_map;
			}
	return maps;
}

char* get_map_arguments(Service* service, int mapCatalogueNumber)
{
	char arguments[MAX_SIZE] = "\0", char_yearsOfStorage[50];
	int mapIndex = find_map(service->repo, mapCatalogueNumber);
	if (mapIndex != -1)
	{
		Map map = get_all(service).maps[mapIndex];
		_itoa(mapCatalogueNumber, arguments, 10);
		strcat(arguments, ",");
		strcat(arguments, get_stateOfDeterioration(&map));
		strcat(arguments, ",");
		strcat(arguments, get_mapType(&map));
		strcat(arguments, ",");
		_itoa(get_yearsOfStorage(map), char_yearsOfStorage, 10);
		strcat(arguments, char_yearsOfStorage);
	}
	return arguments;
}

Repository* get_repo(Service* service)
{
	return service->repo;
}

Container get_all(Service* service) 
{
	return get_data(service->repo);
}
