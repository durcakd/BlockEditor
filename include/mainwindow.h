#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BlockEditorWidget;

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


    QString _textType;
    QString _text;
    BlockEditorWidget *_blockEditorWidged;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

};

#endif // MAINWINDOW_H
