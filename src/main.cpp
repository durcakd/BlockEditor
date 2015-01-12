#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;
    window.setGeometry(100, 100, 800, 500);
    window.show();
    window.openFile("echo.lua");

    return app.exec();
}
