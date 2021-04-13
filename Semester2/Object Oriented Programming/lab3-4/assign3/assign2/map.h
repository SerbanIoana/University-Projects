#pragma once

typedef struct
{
	int mapCatalogueNumber;
	char stateOfDeterioration[50];
	char mapType[50];
	int yearsOfStorage;
}Map;

Map create_map(int mapCatalogueNumber, char stateOfDeterioration[], char mapType[], int yearsOfStorage);
int get_mapCatalogueNumber(Map map);
char* get_stateOfDeterioration(Map* map);
char* get_mapType(Map* map);
int get_yearsOfStorage(Map map);
char* set_stateOfDeterioration(Map* map, char value[]);
char* set_mapType(Map* map, char value[]);
void set_yearsOfStorage(Map* map, int value);
void printMap(Map map);