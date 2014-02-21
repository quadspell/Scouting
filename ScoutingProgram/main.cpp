#include "startup.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon logo("Logo");
    a.setWindowIcon(logo);

    Startup startup;
    startup.show();

    return a.exec();
}
