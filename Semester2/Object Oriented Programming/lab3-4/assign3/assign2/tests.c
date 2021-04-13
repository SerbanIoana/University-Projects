#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "service.h"

void test_dynamicVector()
{
	//printf("test");
	Repository* repo = create_repository();			// use function get_data!!!
	assert(repo->data.length == 0);
	assert(repo->data.capacity == 5);

	Map map1 = create_map(11, "f", "ff", 21);
	Map map2 = create_map(12, "b", "bb", 22);
	Map map3 = create_map(13, "c", "cc", 33);
	Map map4 = create_map(14, "d", "dd", 44);
	Map map5 = create_map(15, "e", "ee", 55);

	add_map(repo,map1);
	add_map(repo, map2);
	add_map(repo, map3);
	add_map(repo, map4);
	add_map(repo, map5);
	assert(repo->data.length == 5);
	assert(repo->data.capacity == 5);

	Map map6 = create_map(16, "g", "gg", 66);
	add_map(repo, map6);
	assert(repo->data.length == 6);
	assert(repo->data.capacity == 10);
}

void test_repository()
{
	//printf("test");
	Repository* repo = create_repository();
	if (repo == NULL)
		assert(0);
	assert(repo->data.length == 0);
	assert(repo->data.capacity == 5);

	Map map = create_map(11, "abcd", "efgh", 21);
	add_map(repo, map);
	assert(repo->data.length == 1);

	delete_map(repo, get_mapCatalogueNumber(map));
	assert(repo->data.length == 0);

	destroy_repository(repo);
}

void test_map()
{
	//printf("test");
	Map map = create_map(11, "f", "ff", 21);
	assert(get_mapCatalogueNumber(map) == 11);
	assert(strcmp(get_stateOfDeterioration(&map), "f") == 0);
	assert(strcmp(get_mapType(&map), "ff") == 0);
	assert(get_yearsOfStorage(map) == 21);
}

void add_map_ValidInput_Added()
{
	//printf("test");
	Repository* repo = create_repository();
	//Service* service = create_service(repo);
	Map map = create_map(11, "abcd", "zzzz", 101);
	int result = add_map(repo, map);
	assert(result == 1);
	assert(repo->data.length == 1);
	assert(repo->data.maps[0].mapCatalogueNumber == get_mapCatalogueNumber(map));
	assert(strcmp(repo->data.maps[0].stateOfDeterioration, get_stateOfDeterioration(&map)) == 0);
	assert(strcmp(repo->data.maps[0].mapType, get_mapType(&map)) == 0);
	assert(repo->data.maps[0].yearsOfStorage == get_yearsOfStorage(map));
}

void add_map_InvalidInput_Return0()
{
	//printf("test");
	Repository* repo = create_repository();
	Map map1 = create_map(11, "abcd", "zzzz", 101);
	int result = add_map(repo, map1);
	assert(result == 1);
	Map map2 = create_map(11, "rtyu", "pppp", 21);
	result = add_map(repo, map2);
	assert(result == 0);
}

void delete_map_ValidInput_Deleted()
{
	//printf("test");
	Repository* repo = create_repository();
	Map map = create_map(11, "abcd", "zzzz", 101);
	int result = add_map(repo, map);
	assert(result == 1);
	assert(repo->data.length == 1);

	result = delete_map(repo, get_mapCatalogueNumber(map));
	assert(result == 1);
	assert(repo->data.length == 0);
}

void delete_map_InvalidInput_Return0()
{
	//printf("test");
	Repository* repo = create_repository();
	Map map = create_map(11, "abcd", "zzzz", 101);
	int result = delete_map(repo, get_mapCatalogueNumber(map));
	assert(result == 0);
}

void update_map_ValidInput_Updated()
{
	//printf("test");
	Repository* repo = create_repository();
	Map map = create_map(11, "abcd", "zzzz", 101);
	int result = add_map(repo, map);
	assert(result == 1);
	Map map2 = create_map(11, "dddd", "ppp", 234);
	result = update_map(repo, map2);
	assert(result == 1);
	assert(repo->data.maps[0].mapCatalogueNumber == get_mapCatalogueNumber(map2));
	assert(strcmp(repo->data.maps[0].stateOfDeterioration, get_stateOfDeterioration(&map2)) == 0);
	assert(strcmp(repo->data.maps[0].mapType, get_mapType(&map2)) == 0);
	assert(repo->data.maps[0].yearsOfStorage == get_yearsOfStorage(map2));
}

void update_map_InvalidInput_Return0()
{
	//printf("test");
	Repository* repo = create_repository();
	Map map = create_map(11, "abcd", "zzzz", 101);
	int result = add_map(repo, map);
	assert(result == 1);
	Map map2 = create_map(12, "dddd", "ppp", 234);
	result = update_map(repo, map2);
	assert(result == 0);
}

void test_all()
{
	test_dynamicVector();
	test_repository();
	test_map();
	add_map_ValidInput_Added();
	add_map_InvalidInput_Return0();
	delete_map_ValidInput_Deleted();
	delete_map_InvalidInput_Return0();
	update_map_ValidInput_Updated();
	update_map_InvalidInput_Return0();
	printf("all tests done!");
}