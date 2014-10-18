#include <QtGui/QApplication>
#include "controllpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControllPanel w;
    w.show();

    return a.exec();
}
