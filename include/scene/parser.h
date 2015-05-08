#ifndef PARSER_H
#define PARSER_H


#include <LuaState.h>
#include <QString>
#include <QObject>

#include "style/styleutil.h"


class Item;
class Layout;
class Style;
class AbstractElement;
class ElementBuilder;

class Parser : public QObject {
    Q_OBJECT

public:
    static Parser *instance(QString type = "");

    Layout *parse(QString text);
    bool reparse(QString text, AbstractElement **res, int &parsedChars);

    Item *createNewItem(Layout *parent, QString type, QString text);
    Item *createStableItem(Layout *parent, QString text);
    //Item *createChangedItem(Layout *parent, QString text);
    Layout *createNewLayout(Layout *parent, QString type);

signals:
//    void addElementItem( Item* item);
//    void addElementLayout( Layout* layout);
    void addElementStyle( Style* style);
//    void parsingFinished();

private:
    static Parser *_instance;
    Parser(QString type);


    void init();
    void loadGrammar();
    void loadStyle();

    lua::State _state;
    QString _textType;
    QString _text;
    ElementBuilder *_elementBuilder;

    AbstractElement *_retree;
    Layout *_root;
    int _parsedChars;

};

#endif // MAINWINDOW_H
