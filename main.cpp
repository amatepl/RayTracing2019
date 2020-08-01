#include "applicationwindow.h"

#include <QApplication>

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    ApplicationWindow mainWindow;

    mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.show();

    return app.exec();
}

