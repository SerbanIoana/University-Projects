#include "repo.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Repository* create_repository()
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (NULL == repo) {
		return NULL;
	}
	repo->data.length = 0;
	repo->data.capacity = 5;
	repo->data.maps = (Map*)malloc(repo->data.capacity * sizeof(Map));
	return repo;
}

void resize(Repository* repo)
{
	if (repo == NULL)
		return;
	if (repo->data.capacity == 0)
		repo->data.capacity = 1;

	repo->data.capacity *= 2;
	Map* new_maps = (Map*)malloc(repo->data.capacity * sizeof(Map));
	if (new_maps == NULL)
		return;
	for (int i = 0; i < repo->data.length; ++i)
		new_maps[i] = repo->data.maps[i];

	free(repo->data.maps);
	repo->data.maps = new_maps;
}

void destroy_repository(Repository* repo)
{
	free(repo);
}

int find_map(Repository* repo, int mapCatalogueNumber)
{
	int i;
	for (i = 0; i < repo->data.length; i++)
	{
		if (get_mapCatalogueNumber(repo->data.maps[i]) == mapCatalogueNumber)
			return i;
	}
	return -1;
}

int add_map(Repository* repo, Map map)
{
	int position = find_map(repo, get_mapCatalogueNumber(map));
	if (position == -1)		//map not found
	{
		if (repo->data.length == repo->data.capacity)
			resize(repo);
		repo->data.maps[repo->data.length++] = map;
		return 1;		//map added successfully
	}
	else
		return 0;
}

int delete_map(Repository* repo, int mapCatalogueNumber)
{
	int i, position = find_map(repo, mapCatalogueNumber);
	if (position == -1)
		return 0;
	else
	{
		for (i = position; i < repo->data.length - 1; i++)
			repo->data.maps[i] = repo->data.maps[i + 1];
		repo->data.length--;
		return 1;		//map deleted successfully
	}
}

int update_map(Repository* repo, Map new_map)
{
	int position = find_map(repo, get_mapCatalogueNumber(new_map));
	if (position == -1)
		return 0;
	else
	{
		set_yearsOfStorage(&repo->data.maps[position], get_yearsOfStorage(new_map));
		set_mapType(&repo->data.maps[position], get_mapType(&new_map));
		set_stateOfDeterioration(&repo->data.maps[position], get_stateOfDeterioration(&new_map));
		return 1;		//map updated successfully
	}
}

Map* findMaps_lessThan_yearsOfStorage(Repository* repo, int* numberOfMaps, int maxYearsOfStorage)
{
	Map* maps_lessThan_yearsOfStorage = malloc(sizeof(Map) * MAX_SIZE);
	//numberOfMaps = 0;
	for (int i = 0; i < repo->data.length; i++)
		if (get_yearsOfStorage(repo->data.maps[i]) < maxYearsOfStorage) 
		{
			maps_lessThan_yearsOfStorage[*numberOfMaps] = repo->data.maps[i];
			*numberOfMaps = *numberOfMaps + 1;
		}

	return maps_lessThan_yearsOfStorage;
}

int get_lenght(Repository* repo)
{
	return repo->data.length;
}

Container get_data(Repository* repo)
{
	return repo->data;
}