#ifndef PARSER_H
#define PARSER_H


#include <LuaState.h>
#include <QString>
#include <QObject>

class Item;
class Layout;

class Parser : public QObject {
    Q_OBJECT

public:
    Parser(QString type);
    void parse(QString text);

signals:
    void addElementItem( Item* item);
    void addElementLayout( Layout* layout);


private:

    void init();
    void loadGrammar();

    lua::State _state;
    QString _textType;
    QString _text;

};

#endif // MAINWINDOW_H
