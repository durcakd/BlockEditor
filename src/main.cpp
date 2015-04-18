#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;

    window.show();
     window.openFile("examples_scripts/echo.lua");

    return app.exec();
}
