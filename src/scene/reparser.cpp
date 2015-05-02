#include "scene/reparser.h"
#include <QDebug>

#include "item/abstractelement.h"
#include "item/item.h"
#include "item/layout.h"
//#include "item/state/elementstate.h"
//#include "item/state/elementinvalid.h"
//#include "item/state/elementvalid.h"

#include "scene/blockscene.h"

Reparser::Reparser()
    : ElementObserver() {
}

void Reparser::update(AbstractElement *element) {
    qDebug() << " REPARSER update: "<< element->textE();




}

//    bool ok;
//    Layout *parent = element->getLayoutParrent();
//    qDebug() << "1. "<<parent->textE();
//    while (parent != NULL && parent->textE().length() == element->textE().length()) {
//        parent = parent->getLayoutParrent();
//        qDebug() << "2. "<<parent->textE();

//    }
//    AbstractElement *p = parent;
//    if (p == NULL) {
//        qDebug() << " zeby root";

//        p = element;
//    }
//    qDebug() << "3. "<<p->textE();


//    ok = Parser::instance()->reparse(p->textE());
//    if (!ok) {qDebug() << "Reparsing parent error";}
//    if (ok) {qDebug() << "Reparsing parent ok";}
//    //ok = Parser::instance()->reparse(BlockScene::instance()->root()->textE());
//    //if (!ok) {qDebug() << "Reparsing error";}

//    if (ok) {
//        element->setState( new ElementValid);
//    } else {
//        element->setState( new ElementInvalid);
//    }

