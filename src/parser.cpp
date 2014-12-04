#include "parser.h"
#include "scene/item.h"
#include "scene/layout.h"
#include "style/style.h"
#include <QDebug>

Parser::Parser(QString type) :
    QObject()
{
    _textType = type;
    init();
    loadGrammar();
    loadStyle();
}



void Parser::init() {
      //_state.set("send_commit");
    _state.set("addBasicItem",
               [this] (lua::String elementType,
                       lua::String elementText,
                       lua::Pointer parentPointer,
                       lua::Integer elementIndex)
               -> lua::Pointer
    {
        Item *newItem= new Item( elementType, elementText, _styleUtil.getStyle(elementType), static_cast<Layout*>(parentPointer));
        emit addElementItem(newItem);
        return newItem;
    });
    _state.set("addBasicLayout",
               [this] (lua::String elementType,
                       lua::Pointer parentPointer,
                       lua::Integer elementIndex)
               -> lua::Pointer
    {
        Layout *newLayout= new Layout( elementType, _styleUtil.getStyle(elementType), static_cast<Layout*>(parentPointer));
        emit addElementLayout(newLayout);

        return newLayout;
    });

    _state.doFile("scripts/init.lua");
    _state.doFile("scripts/core.lua");

}

void Parser::loadStyle()
{
    _state.set("addStyle",
               [this] (lua::String elementType,
                       lua::String orientation,
                       lua::Boolean isItem,
                       lua::Boolean isLayout)
               -> lua::Pointer
    {
        Style *newStyle = new Style(elementType);
        newStyle->setIsItem(isItem);
        newStyle->setIsLayout(isLayout);
        newStyle->setOrientation( orientation);

        _styleUtil.addStyle(newStyle);
        //emit addElementStyle( newStyle);

        return newStyle;
    });

    qDebug() << "Load styles...";
    _state["loadStyles"]();
}

void Parser::loadGrammar() {
    try {
        _state["loadGrammarAndStyle"].call( _textType.toStdString().c_str());
    }
    catch (lua::RuntimeError ex) {
        //QMessageBox msgBox;
        //msgBox.setText(QString("Error while loading grammar style: ").append(_textType));
       // msgBox.setInformativeText(ex.what());
        //msgBox.setStandardButtons(QMessageBox::Ok);
        //msgBox.exec();
        qDebug() << "Error while loading grammar style: " << _textType;
        qDebug() << ex.what();
        throw std::runtime_error(ex.what());
    }
}

void Parser::parse(QString text) {
    qDebug() << "Request text reparse...";
    _state["parseTextNew"]( text.toStdString().c_str());
}
