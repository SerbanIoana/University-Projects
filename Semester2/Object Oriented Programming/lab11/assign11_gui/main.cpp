#include "assign11_gui.h"
#include <QtWidgets/QApplication>
#include "fileRepository.h"
#include "service.h"
#include "GUI.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    FileRepository repo{"tapes.txt"};
    Service service{ repo };

    GUI gui{service};
    gui.show();

    return a.exec();
}
