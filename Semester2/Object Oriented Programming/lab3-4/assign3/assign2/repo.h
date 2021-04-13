#pragma once
#include "map.h"
#define MAX_SIZE 200

//typedef struct {
	//Map maps[MAX_SIZE];
	//int length;
//} Container;

typedef struct {
	Map* maps;
	int length;
	int capacity;
} Container;

typedef struct {
	Container data;
} Repository;

Repository* create_repository();
void destroy_repository(Repository* repo);
int find_map(Repository* repo, int mapCatalogueNumber);
int add_map(Repository* repo, Map map);
int delete_map(Repository* repo, int mapCatalogueNumber);
int update_map(Repository* repo, Map new_map);
Map* findMaps_lessThan_yearsOfStorage(Repository* repo, int* numberOfMaps, int maxYearsOfStorage);
int get_lenght(Repository* repo);
Container get_data(Repository* repo);