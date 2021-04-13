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
	ui->undo_list = malloc(sizeof(Operation) * MAX_SIZE);
	ui->redo_list = malloc(sizeof(Operation) * MAX_SIZE);
	ui->undo_manager_index = -1;
	ui->number_operations = 0;
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

void list_mapType(Ui* ui, char read_mapType[])
{
	Container data = get_all(ui->service);
	int i;
	
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

	//free()
}

void list_yearsOfStorage(Ui* ui, char read_yearsOfStorage[])
{
	int maxYearsOfStorage = atoi(read_yearsOfStorage);
	int numberOfMaps = 0, i;

	Map* maps_lessThan_yearsOfStorage = getMaps_lessThan_yearsOfStorage(ui->service, &numberOfMaps, maxYearsOfStorage);
	//order_by_stateOfDeterioration(ui->service, maps_lessThan_yearsOfStorage, numberOfMaps);

	for (i = 0; i < numberOfMaps; i++)
		printMap(maps_lessThan_yearsOfStorage[i]);

	free(maps_lessThan_yearsOfStorage);
}

void list_userInput(Ui* ui, char arguments[])
{
	int count = 0;
	char argument[MAX_SIZE];
	char* token;

	token = strtok(arguments, ",");
	if (token != NULL)
	{
		strcpy(argument, token);
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
		argument[strlen(argument) - 1] = '\0';
		if (isalpha(argument[0]))
			list_mapType(ui, argument);
		else if (isdigit(argument[0])) {
			list_yearsOfStorage(ui, argument);
		}
	}
}

void run_console(Ui* ui)
{
	char input[MAX_SIZE], arguments[MAX_SIZE] = "\0";
	char command[MAX_SIZE], undo_command[MAX_SIZE];
	char* token;
	//Operation* undo_list = malloc(sizeof(Operation) * MAX_SIZE);
	//Operation* redo_list = malloc(sizeof(Operation) * MAX_SIZE);
	//int undo_manager_index = -1;
	//int number_operations = 0;

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
			strcpy(command, token);			//add
			token = strtok(NULL, " ");
			while (token != NULL)
			{
				strcat(arguments, token);
				token = strtok(NULL, " ");		//12,b,bb,22
			}

			//command is the command word
			//arguments - arguments for command

			if (strcmp(command, "add") == 0)
			{
				ui->undo_manager_index++;
				Operation undo_operation;
				Operation redo_operation;
				strcpy(redo_operation.command, "add");
				strcpy(redo_operation.arguments, arguments);
				ui->redo_list[ui->undo_manager_index] = redo_operation;

				add_map_data(ui, arguments);

				if (ui->undo_manager_index < ui->number_operations)
					ui->number_operations = ui->undo_manager_index + 1;
				else
					ui->number_operations++;

				char* undo_argument;
				strcpy(undo_operation.command, "delete");
				undo_argument = strtok(arguments, ",");
				strcpy(undo_operation.arguments, undo_argument);
				ui->undo_list[ui->undo_manager_index] = undo_operation;
				
			}
			else if (strcmp(command, "delete") == 0)
			{
				ui->undo_manager_index++;
				Operation undo_operation;
				Operation redo_operation;
				strcpy(redo_operation.command, "delete");
				strcpy(redo_operation.arguments, arguments);
				ui->redo_list[ui->undo_manager_index] = redo_operation;

				char delete_arguments[50] = "\0";
				strcpy(delete_arguments, arguments);
				int mapCatalogueNumber = atoi(strtok(delete_arguments, ","));
				char* undo_arguments = get_map_arguments(ui->service, mapCatalogueNumber);
				strcpy(undo_operation.command, "add");
				strcpy(undo_operation.arguments, undo_arguments);
				ui->undo_list[ui->undo_manager_index] = undo_operation;

				delete_map_data(ui, arguments);
				if (ui->undo_manager_index < ui->number_operations)
					ui->number_operations = ui->undo_manager_index + 1;
				else
					ui->number_operations++;
			}
			else if (strcmp(command, "update") == 0)
			{
				ui->undo_manager_index++;
				Operation undo_operation;
				Operation redo_operation;
				strcpy(redo_operation.command, "update");
				strcpy(redo_operation.arguments, arguments);
				ui->redo_list[ui->undo_manager_index] = redo_operation;

				char update_arguments[50] = "\0";
				strcpy(update_arguments, arguments);
				int mapCatalogueNumber = atoi(strtok(update_arguments, ","));
				char* undo_arguments = get_map_arguments(ui->service, mapCatalogueNumber);
				strcpy(undo_operation.command, "update");
				strcpy(undo_operation.arguments, undo_arguments);
				ui->undo_list[ui->undo_manager_index] = undo_operation;

				update_map_data(ui, arguments);
				if (ui->undo_manager_index < ui->number_operations)
					ui->number_operations = ui->undo_manager_index + 1;
				else
					ui->number_operations++;
			}
			else if (strcmp(command, "undo\n") == 0)
			{
				if (ui->undo_manager_index < 0 || ui->undo_manager_index >= ui->number_operations)
					printf("Nothing to undo!\n");
				else
				{
					char last_command[MAX_SIZE] = "\0", last_arguments[MAX_SIZE] = "\0";
					strcpy(last_command, ui->undo_list[ui->undo_manager_index].command);
					strcpy(last_arguments, ui->undo_list[ui->undo_manager_index].arguments);

					if (strcmp(last_command, "delete") == 0)
						delete_map_data(ui, last_arguments);
					else if (strcmp(last_command, "add") == 0)
						add_map_data(ui, last_arguments);
					else if (strcmp(last_command, "update") == 0)
						update_map_data(ui, last_arguments);

					ui->undo_manager_index--;
				}
			}
			else if (strcmp(command, "redo\n") == 0)
			{
				if (ui->undo_manager_index < -1 || ui->undo_manager_index >= ui->number_operations - 1)
					printf("Nothing to redo!\n");
				else
				{
					ui->undo_manager_index++;

					char last_command[MAX_SIZE] = "\0", last_arguments[MAX_SIZE] = "\0";
					strcpy(last_command, ui->redo_list[ui->undo_manager_index].command);
					strcpy(last_arguments, ui->redo_list[ui->undo_manager_index].arguments);

					if (strcmp(last_command, "delete") == 0)
						delete_map_data(ui, last_arguments);
					else if (strcmp(last_command, "add") == 0)
						add_map_data(ui, last_arguments);
					else if (strcmp(last_command, "update") == 0)
						update_map_data(ui, last_arguments);
				}
			}

			else if (strcmp(command, "list\n") == 0)
				list_all(ui);
			else if (strcmp(command, "list") == 0)
				list_userInput(ui, arguments);
			else
				printf("Invalid command!\n");
				
		}
	}

}