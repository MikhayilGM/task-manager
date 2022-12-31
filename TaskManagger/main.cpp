#include "taskmanagermainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskManagerMainWindow w;
    w.move(500, 300);
    w.resize(600, 500);
    w.show();
    return a.exec();
}
