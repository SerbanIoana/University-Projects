#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_SIZE 200

Ui* create_ui(Service* service)
{
	Ui* ui = (Ui*)malloc(sizeof(Ui));
	if (ui == NULL)
		return NULL;
	ui->service = service;
	return ui;
}

void add_map_data(Ui* ui, char arguments[])
{
	int mapCatalogueNumber, yearsOfStorage, count = 0;
	char stateOfDeterioration[MAX_SIZE], mapType[MAX_SIZE], tokens[5][MAX_SIZE];
	char* token;

	token = strtok(arguments, ",");
	while (token != NULL)
	{
		strcpy(tokens[count++], token);
		token = strtok(NULL, ",");
	}

	if (count == 4)
	{
		mapCatalogueNumber = atoi(tokens[0]);
		strcpy(stateOfDeterioration, tokens[1]);
		strcpy(mapType, tokens[2]);
		yearsOfStorage = atoi(tokens[3]);

		int result = add_map_service(ui->service, mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
		if (result == 0)
			printf("No!\n");
	}
	else
		printf("No!\n");
}

void delete_map_data(Ui* ui, char arguments[])
{
	int mapCatalogueNumber, count = 0;
	char* token;

	token = strtok(arguments, ",");
	if (token != NULL)
	{
		mapCatalogueNumber = atoi(token);
		count++;
		token = strtok(NULL, ",");
		if (token != NULL)
		{
			count = 0;
			printf("No!\n");
		}
	}
	
	if (count == 1)
	{
		int result = delete_map_service(ui->service, mapCatalogueNumber);
		if (result == 0)
			printf("No!\n");
	}
}

void update_map_data(Ui* ui, char arguments[])
{
	int mapCatalogueNumber, new_yearsOfStorage, count = 0;
	char new_stateOfDeterioration[MAX_SIZE], new_mapType[MAX_SIZE], tokens[5][MAX_SIZE];
	char* token;

	token = strtok(arguments, ",");
	while (token != NULL)
	{
		strcpy(tokens[count++], token);
		token = strtok(NULL, ",");
	}

	if (count == 4)
	{
		mapCatalogueNumber = atoi(tokens[0]);
		strcpy(new_stateOfDeterioration, tokens[1]);
		strcpy(new_mapType, tokens[2]);
		new_yearsOfStorage = atoi(tokens[3]);

		int result = update_map_service(ui->service, mapCatalogueNumber, new_stateOfDeterioration, new_mapType, new_yearsOfStorage);
		if (result == 0)
			printf("No!\n");
	}
	else
		printf("No!\n");
}

void list_all(Ui* ui)
{
	Container data = get_all(ui->service);
	int i;

	for (i = 0; i < data.length; i++)
	{
		Map map = data.maps[i];
		printMap(map);
	}
}

void list_mapType(Ui* ui, char arguments[])
{
	int count = 0;
	char read_mapType[MAX_SIZE];
	char* token;

	token = strtok(arguments, ",");
	if (token != NULL)
	{
		strcpy(read_mapType, token);
		count++;
		token = strtok(NULL, ",");
		if (token != NULL)
		{
			count = 0;
			printf("No!\n");
		}
	}

	if (count == 1)
	{
		read_mapType[strlen(read_mapType) - 1] = '\0';
		Container data = get_all(ui->service);
		int i;
		//get_mapType(data.maps[i])
		//data.maps[i].mapType
		for (i = 0; i < data.length; i++)
		{
			char mapType[MAX_SIZE];
			strcpy(mapType, get_mapType(&data.maps[i]));
			if (strcmp(mapType, read_mapType) == 0)
			{
				Map map = data.maps[i];
				printMap(map);
			}
		}
	}
}

void run_console(Ui* ui)
{
	char input[MAX_SIZE], arguments[MAX_SIZE] = "\0", command[MAX_SIZE];
	char* token;

	while (1)
	{
		printf("Give command: ");
		fgets(input, sizeof(input), stdin);

		if (strcmp(input, "exit\n") == 0)
			break;
		else
		{
			strcpy(arguments, "\0");
			token = strtok(input, " ");		//command 
			strcpy(command, token);
			token = strtok(NULL, " ");
			while (token != NULL)
			{
				strcat(arguments, token);
				token = strtok(NULL, " ");
			}

			//printf("%s\n", command);
			//printf("%s\n", arguments);

			//command is the command word
			//arguments - arguments for command

			if (strcmp(command, "add") == 0)
				add_map_data(ui, arguments);
			else if (strcmp(command, "delete") == 0)
				delete_map_data(ui, arguments);
			else if (strcmp(command, "update") == 0)
				update_map_data(ui, arguments);
			else if (strcmp(command, "list\n") == 0)
				list_all(ui);
			else if (strcmp(command, "list") == 0)
				list_mapType(ui, arguments);
			else
				printf("Invalid command!\n");
				
		}
	}

}