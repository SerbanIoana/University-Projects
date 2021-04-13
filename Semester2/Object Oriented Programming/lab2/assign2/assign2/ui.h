#pragma once
#include "service.h"

typedef struct
{
	Service* service;
}Ui;

Ui* create_ui(Service* service);
void add_map_data(Ui* ui, char arguments[]);
void delete_map_data(Ui* ui, char arguments[]);
void update_map_data(Ui* ui, char arguments[]);
void list_all(Ui* ui);
void list_mapType(Ui* ui, char arguments[]);
void run_console(Ui* ui);