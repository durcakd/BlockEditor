#include "mainwindow.h"

#include <QTextEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QtWidgets>

//#include "blockscene.h"


MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolbars();


    textEdit = new QTextEdit(this);
    scene = new BlockScene();
    view = new QGraphicsView(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(view);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    setWindowTitle(tr("BlockEditor"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    //fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    //itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    //itemMenu->addAction(toFrontAction);
    //itemMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    //aboutMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{

}

void MainWindow::createToolbars()
{

}
