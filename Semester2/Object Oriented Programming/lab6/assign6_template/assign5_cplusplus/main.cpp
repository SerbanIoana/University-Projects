#include <iostream>
#include "tape.h"
#include "dynamicVector.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "tests.h"

int main()
{
	/*
	Repository repo{};
	Service service{ repo };
	
	Date date{ 9,12,2019 };
	service.service_add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 11,4,2019 };
	service.service_add_tape("zzz", "ccc", date1, 3, "vvv");
	Date date2{ 22,5,2019 };
	service.service_add_tape("qqq", "www", date2, 5, "eee");
	Date date3{ 3,6,2019 };
	service.service_add_tape("rrr", "ttt", date3, 8, "yyy");

	Ui ui{ service };
	ui.run();
	*/
	test_all();
}
