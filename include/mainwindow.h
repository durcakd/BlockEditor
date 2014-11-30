#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BlockScene;
class QGraphicsView;
class QTextEdit;
class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void createActions();
    void createMenus();
    void createToolbars();


    QTextEdit *textEdit;
    BlockScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

};

#endif // MAINWINDOW_H
