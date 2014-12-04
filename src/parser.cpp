#include "parser.h"
#include <QDebug>

Parser::Parser(QString type)
{
    _textType = type;
    init();
    loadGrammar();
}



void Parser::init() {
     //_state.set("send_addItem");
     //_state.set("send_addGrid");
      //_state.set("send_updateItem");
      //_state.set("send_removeItem");
      //_state.set("send_commit");
    _state.doFile("scripts/init.lua");
    _state.doFile("scripts/core.lua");

    //setUpdateCallback(std::bind(&GraphicText::updateElementsOnScene, this, _1, _2, _3));
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
