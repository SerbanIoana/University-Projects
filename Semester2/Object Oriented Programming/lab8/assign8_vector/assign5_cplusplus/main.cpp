#include <iostream>
#include "tape.h"
#include "repository.h"
#include "fileRepository.h"
#include "service.h"
#include "ui.h"
#include "tests.h"

int main()
{
	
	FileRepository repo{};
	Service service{ repo };

	Ui ui{ service };
	ui.run();
	

	//test_all();
}
