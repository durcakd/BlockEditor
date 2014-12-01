#include "mainwindow.h"

#include <QTextEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QWidget>
#include <QMessageBox>
#include <QDebug>

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
    //fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    //itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(tr("&About"), this, SLOT(about()));
    //aboutMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
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
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Lua scripts (*.lua)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {

            QFileInfo fileInfo(file);

            _textType = fileInfo.suffix();

            QTextStream in(&file);
            _text = in.readAll();
            lineEditor->setPlainText(_text);
            file.close();


            // Nacitame core
            _state.doFile("scripts/init.lua");
            _state.doFile("scripts/core.lua");
            //_state->setUpdateCallback(std::bind(&GraphicText::updateElementsOnScene, this, _1, _2, _3));
            try {

                _state["loadGrammarAndStyle"].call( _textType.toStdString().c_str());
            }
            catch (lua::RuntimeError ex) {
                QMessageBox msgBox;
                msgBox.setText(QString("Error while loading grammar style: ").append(_textType));
                msgBox.setInformativeText(ex.what());
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();

                throw std::runtime_error(ex.what());
            }

           qDebug() << "Request text reparse...";

            _state["parseText"]( _text.toStdString().c_str());
        }
    }
}

