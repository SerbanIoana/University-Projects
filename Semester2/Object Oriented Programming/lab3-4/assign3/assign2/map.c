#include "map.h"
#include <string.h>
#include <stdio.h>

Map create_map(int mapCatalogueNumber, char stateOfDeterioration[], char mapType[], int yearsOfStorage)
{
	Map map;
	map.mapCatalogueNumber = mapCatalogueNumber;
	strcpy(map.stateOfDeterioration, stateOfDeterioration);
	strcpy(map.mapType, mapType);
	map.yearsOfStorage = yearsOfStorage;
	return map;
}

int get_mapCatalogueNumber(Map map)
{
	return map.mapCatalogueNumber;
}

char* get_stateOfDeterioration(Map* map)
{
	return map->stateOfDeterioration;
}

char* get_mapType(Map* map)
{
	return map->mapType;
}

int get_yearsOfStorage(Map map)
{
	return map.yearsOfStorage;
}

char* set_stateOfDeterioration(Map* map, char value[])
{
	strcpy(map->stateOfDeterioration, value);
}

char* set_mapType(Map* map, char value[])
{
	strcpy(map->mapType, value);
}

void set_yearsOfStorage(Map* map, int value)
{
	map->yearsOfStorage = value;
}

void printMap(Map map)
{
	printf("Catalogue number: %d, State of deterioration: %s, Type: %s, Years of storage: %d\n", map.mapCatalogueNumber, map.stateOfDeterioration, map.mapType, map.yearsOfStorage);
}