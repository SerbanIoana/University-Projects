#include <iostream>
#include "tape.h"
#include "repository.h"
#include "fileRepository.h"
#include "service.h"
#include "ui.h"

int main()
{
	Repository* repo = new Repository{};
	Repository* agent_repo = new Repository{};
	Service service{ repo, agent_repo };

	Ui ui{ service };
	ui.run();

	//test_all();
}
