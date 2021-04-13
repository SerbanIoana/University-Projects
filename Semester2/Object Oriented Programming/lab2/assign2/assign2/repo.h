#pragma once
#include "map.h"

typedef struct {
	Map maps[100];
	int length;
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
int get_lenght(Repository* repo);
Container get_data(Repository* repo);