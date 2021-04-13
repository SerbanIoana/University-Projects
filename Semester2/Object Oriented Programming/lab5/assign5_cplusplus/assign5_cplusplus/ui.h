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
	static void print_menu();

	Date format_creationDate(const std::string& input_date);

	void ui_add_tape(char* arguments);
	void ui_update_tape(char* arguments);
	void ui_delete_tape(char* arguments);
	void ui_list();
};