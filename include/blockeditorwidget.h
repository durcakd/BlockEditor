#ifndef BLOCKEDITORWIDGET_H
#define BLOCKEDITORWIDGET_H

#include <QWidget>

class BlockScene;
class QGraphicsView;
class QGraphicsScene;
class Parser;

class BlockEditorWidget: public QWidget
{
    Q_OBJECT

public:
    BlockEditorWidget();
    QString getEditedText();

public slots:
    void editText(const QString text);

protected:
    void clearPreviousEditedText();

private:

    BlockScene *scene;
    QGraphicsView *view;
    Parser *parser;

    QString _textType;
    QString _text;
};

#endif // MAINWINDOW_H
