#include "mainwindow.h"

#include <QTextEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QtWidgets>

#include "lineeditor.h"
#include "blockscene.h"
#include "highlighter.h"


MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolbars();

    lineEditor = new LineEditor(this);
    highlighter = new Highlighter(lineEditor->document());

    scene = new BlockScene();
    view = new QGraphicsView(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(lineEditor);
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
    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    //itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(tr("&About"), this, SLOT(about()));
    aboutMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::createActions() { }

void MainWindow::createToolbars() { }


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Block Editor"),
                tr("<p>The <b>Block Editor</b> is prototype of hybrid text and visual editor for Lua script language, that use LPEG for syntax analysm of edited code.</p>"));
}

void MainWindow::newFile()
{
    lineEditor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            lineEditor->setPlainText( file.readAll());
    }
}
