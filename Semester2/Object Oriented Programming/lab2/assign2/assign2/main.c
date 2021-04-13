#include "repo.h"
#include "service.h"
#include "ui.h"
#include <stdio.h>


int main()
{
	Repository* repo = create_repository();
	Service* service = create_service(repo);
	Ui* ui = create_ui(service);

	Map map = create_map(11, "a", "aa", 21);
	add_map_service(service, 12, "b", "bb", 22);
	add_map_service(service, 13, "c", "cc", 33);
	add_map_service(service, 14, "d", "dd", 44);
	//delete_map_service(service, 13);


	run_console(ui);
	return 0;
}
