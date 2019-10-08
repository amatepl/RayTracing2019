#include "MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])

    /*
     * The main function consist only on calling the Qt windows objects, the main algorithm and functions are defined in the room.cpp sourcecode, and is
     * instantiated in the MainWindow object.
     */

{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.showMaximized();

    return a.exec();
}
