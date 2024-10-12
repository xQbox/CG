#include "myscene.h"
#include "mymainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyScene w;
    MyMainWindow mainWindow(nullptr, &w);
    mainWindow.show();

//    w.show();



    return a.exec();
}
