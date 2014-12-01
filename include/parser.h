#ifndef PARSER_H
#define PARSER_H


#include <LuaState.h>
#include <QString>

class Parser {

public:
    Parser(QString type);
    void parse(QString text);

private:

    void init();
    void loadGrammar();

    lua::State _state;
    QString _textType;
    QString _text;

};

#endif // MAINWINDOW_H
