#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BlockScene;
class QGraphicsView;
class QTextEdit;
class QGraphicsScene;
class LineNumberArea;
class LineEditor;
class Highlighter;
class Parser;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void about();
    void newFile();
    void openFile(const QString &path = QString());

private:
    //void setupEditor();
    //void setupFileMenu();
    //void setupHelpMenu();

    void createActions();
    void createMenus();
    void createToolbars();

    QTextEdit *textEdit;
    BlockScene *scene;
    QGraphicsView *view;
    LineNumberArea *lineNumberArea;
    LineEditor *lineEditor;
    Highlighter *highlighter;
    Parser *parser;


    QString _textType;
    QString _text;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

};

#endif // MAINWINDOW_H
