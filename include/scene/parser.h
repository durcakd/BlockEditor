#ifndef PARSER_H
#define PARSER_H


#include <LuaState.h>
#include <QString>
#include <QObject>

#include "style/styleutil.h"


class Item;
class Layout;
class Style;
class ElementBuilder;

class Parser : public QObject {
    Q_OBJECT

public:
    Parser(QString type);
    void parse(QString text);
    Item *createNewItem(ElementBuilder &builder, Layout *parent, QString type, QString text);
    Item *createNewStableItem(ElementBuilder &builder, Layout *parent, QString text);
    Layout *createNewLayout(ElementBuilder &builder, Layout *parent, QString type);

signals:
    void addElementItem( Item* item);
    void addElementLayout( Layout* layout);
    void addElementStyle( Style* style);
    void parsingFinished();

private:

    void init();
    void loadGrammar();
    void loadStyle();

    lua::State _state;
    QString _textType;
    QString _text;
    ElementBuilder *_elementBuilder;

};

#endif // MAINWINDOW_H
