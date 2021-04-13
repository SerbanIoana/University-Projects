#include "SurveillanceTapesGUI.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "appConfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    AppConfigurator configurator{ "app_config.txt" };
    GeneralRepository* repo = configurator.create_admin_repository();
    GeneralRepository* agent_repo = configurator.create_agent_repository();

    /*
    unique_ptr<FileRepository> repo = make_unique<FileRepository>("tapes.txt");
    unique_ptr<FileRepository> agent_repo = make_unique<CSVRepo>();
    */

    Service service{ repo, agent_repo };

    SurveillanceTapesGUI gui{service};
    gui.show();

    return a.exec();
}
