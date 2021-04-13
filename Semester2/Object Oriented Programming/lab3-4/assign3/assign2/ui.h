#pragma once
#include "service.h"
#include "operation.h"

typedef struct
{
	Service* service;
	Operation* undo_list;
	Operation* redo_list;
	int undo_manager_index;
	int number_operations;
}Ui;

Ui* create_ui(Service* service);
void add_map_data(Ui* ui, char arguments[]);
void delete_map_data(Ui* ui, char arguments[]);
void update_map_data(Ui* ui, char arguments[]);
void list_all(Ui* ui);
void list_mapType(Ui* ui, char read_mapType[]);
void list_yearsOfStorage(Ui* ui, char read_yearsOfStorage[]);
void list_userInput(Ui* ui, char arguments[]);
void run_console(Ui* ui);