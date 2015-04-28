#include "scene/parser.h"
#include "item/item.h"
#include "item/layout.h"
#include "style/style.h"
#include <QDebug>
#include <QStringBuilder>
#include <item/state/elementvalid.h>
#include <item/state/elementstable.h>
#include <item/state/elementchanged.h>
#include <item/elementbuilder.h>
#include <item/standardelementbuilder.h>
#include <QGraphicsLinearLayout>


Parser *Parser::_instance = NULL;

Parser *Parser::instance(QString type) {
    if (_instance == NULL) {
        if (type.isEmpty()) {
            qDebug() << "Warning: parser type undefined!";
        }
        _instance = new Parser(type);
    }
    return _instance;
}

Parser::Parser(QString type) :
    QObject()
{
    _textType = type;
    _elementBuilder = new StandardElementBuilder();
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
        //elementText.
        QString text = elementText;
        QString onlyText;
        QString afterText;

        QString::ConstIterator it;
        for (it = text.constBegin(); it != text.constEnd(); it++) {
            //qDebug() << "--------- " << *it << "  space:"<<it->isSpace() <<"  isLN:"<<it->isLetterOrNumber() <<"  isPrint:"<<it->isPrint() <<"  isSymbol:"<<it->isSymbol();
            if (it->isSpace()) {
                afterText += *it;
            } else {
                onlyText += *it;
            }
        }
        qDebug()<<" >"<< onlyText <<"<>"<<afterText;
        Item *newItem = createNewItem( static_cast<Layout*>(parentPointer), elementType, onlyText);
        emit addElementItem(newItem);

        if (!afterText.isEmpty()){
            Item *newItem = createStableItem( static_cast<Layout*>(parentPointer), afterText);
            emit addElementItem(newItem);
        }

        return newItem;
    });
    _state.set("addBasicLayout",
               [this] (lua::String elementType,
               lua::Pointer parentPointer,
               lua::Integer elementIndex)
            -> lua::Pointer
    {
        qDebug() << "parsing layout "<< elementType;
        Layout *newLayout= createNewLayout( static_cast<Layout*>(parentPointer), elementType);
        emit addElementLayout(newLayout);
        return newLayout;
    });

    _state.doFile("scripts/init.lua");
    _state.doFile("scripts/core.lua");

}



void Parser::loadStyle()
{
    _state.set("addStyle",
               [this] ( lua::Value style,
               lua::String elementType)
            -> lua::Pointer
    {
        Style *newStyle = new Style(elementType);

        newStyle->setIsItem( style["item"]);
        newStyle->setIsLayout( style["grid"]);
        lua::String object = style["object"];

        if (strcmp(object, "text") == 0){
            lua::Value text = style["text"];
            newStyle->setIsColor( text["isColor"]);
        } else {
            newStyle->setOrientation( object);
        }

        StyleUtil::instance()->addStyle(newStyle);

        return newStyle;
    });

    qDebug() << "Load styles...";
    _state["loadStyles"]();

}

void Parser::loadGrammar()
{
    try {
        _state["loadGrammarAndStyle"].call( _textType.toStdString().c_str());
    }
    catch (lua::RuntimeError ex) {
        //QMessageBox msgBox;
        //msgBox.setText(QString("Error while loading grammar style: ")
        //.append(_textType));
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
    qDebug() << "... parsing DONE";
    emit parsingFinished();
}


Item *Parser::createNewItem(Layout *parent, QString type, QString text) {
    _elementBuilder->buildItem(parent, text);
    _elementBuilder->buildType(type);
    _elementBuilder->buildStyle();
    _elementBuilder->buildState();
    return dynamic_cast<Item*>(_elementBuilder->getElement());
}

Item *Parser::createStableItem(Layout *parent, QString text) {
    _elementBuilder->buildItem(parent, text);
    _elementBuilder->buildType("spaced_text");
    _elementBuilder->buildStyle();
    _elementBuilder->buildState( new ElementStable());
    return dynamic_cast<Item*>(_elementBuilder->getElement());
}

Item *Parser::createChangedItem(Layout *parent, QString text) {
    _elementBuilder->buildItem(parent, text);
    _elementBuilder->buildType("changed_text");
    _elementBuilder->buildStyle();
    _elementBuilder->buildState( new ElementChanged);
    return dynamic_cast<Item*>(_elementBuilder->getElement());
}

Layout *Parser::createNewLayout(Layout *parent, QString type) {
    //qDebug() << "inside building layout , parent = "<< parent;
    _elementBuilder->buildLayout(parent);
    _elementBuilder->buildType(type);
    _elementBuilder->buildStyle();
    _elementBuilder->buildState();
    return dynamic_cast<Layout*>(_elementBuilder->getElement());
}
