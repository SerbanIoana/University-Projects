#pragma once
#include "service.h"
#include <vector>
#include <string>

class Ui
{
private:
	Service service;
public:
	Ui(const Service& service) : service(service) {}
	void run();

private:
	static void print_directions();
	static void print_menu();
	static void print_agent_menu();

	void add_tape_data(char* arguments);
	void update_tape_data(char* arguments);
	void delete_tape_data(char* arguments);
	void list();

	void next_tape_data();
	void save_tape_data(char* arguments);
	void list_filmedAt(char* arguments);
	void my_list();

	void file_location_data(string arguments);
	void mylist_location_data(string arguments);

	void admin_mode();
	void agent_mode();
};