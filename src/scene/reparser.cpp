#include "scene/reparser.h"
#include <QDebug>

#include "item/abstractelement.h"
#include "item/item.h"
#include "item/layout.h"
#include "scene/parser.h"
//#include "item/state/elementstate.h"
//#include "item/state/elementinvalid.h"
//#include "item/state/elementvalid.h"

#include "scene/blockscene.h"
#include "item/abstractelement.h"
#include "item/layout.h"


Reparser::Reparser()
    : ElementObserver() {
}

Reparser::~Reparser() {
    qDebug() << "destructor";
}

void Reparser::update(AbstractElement *element) {
    qDebug() << " REPARSER update: "<< element->textE();


    AbstractElement *fParent = findBiggerParnet(element);
    if (fParent == NULL) {
        qDebug() << " warning f root";
        fParent = element;
    }
    //reparse(fParent);

    AbstractElement *sParent = findBiggerParnet(fParent);
    if (sParent == NULL) {
        qDebug() << " warning s root";
        sParent = fParent;
    }
    reparse(sParent);
    qDebug() << " end REPARSER";
}

void Reparser::reparse(AbstractElement *element) {
    int parsedChars = 0;
    AbstractElement *res = NULL;

    QString text = element->textE();
    qDebug()<< "text len = " << text.length();

    bool ok = Parser::instance()->reparse(text, &res, parsedChars);
    if (!ok) {qDebug() << "Reparsing parent error";}
    if (ok) {qDebug() << "Reparsing parent ok";}

    if (ok) {
        res = firstChild(res);
        qDebug() << "parsed c= "<< parsedChars;
        qDebug() << "res = "<< res->getType();
        Layout* layout = dynamic_cast<Layout*>(res);
        if (layout) {
            qDebug() << "count = "<< layout->count();
        }
        replaceElement(element, res);
        //element->setState( new ElementValid);
    } else {
        //element->setState( new ElementInvalid);
    }
}

void Reparser::replaceElement(AbstractElement *oldElem, AbstractElement*newElem) {
    Layout *parent = oldElem->getLayoutParrent();
    if (NULL == parent) {
        // TODO ????? maybe new ROOT



    } else {
        parent->insertBehind(oldElem, newElem);
        BlockScene::instance()->addItem( dynamic_cast<QGraphicsItem*>(newElem), true);

        parent->removeElement(oldElem);
        BlockScene::instance()->removeItem( dynamic_cast<QGraphicsItem *>(oldElem), true);
        qDebug() << "removed";

        parent->updateChildNeighbors();

// focus  TODO

    }


}


Layout *Reparser::findBiggerParnet(AbstractElement *element) {
    Layout *parent = element->getLayoutParrent();
    int elementTextLen = element->textE().length();
    while (parent != NULL && parent->textE().length() == elementTextLen) {
        parent = parent->getLayoutParrent();
    }
    return parent;
}


AbstractElement *Reparser::firstChild(AbstractElement *parent) {
    Layout *layout = dynamic_cast<Layout*>(parent);
    if (layout) {
        return firstChild(layout);
    }
    return NULL;
}

AbstractElement *Reparser::firstChild(Layout *parent) {
    if (parent->count() != 1) {
        qDebug () << "WARNING!!! reparser:firstChild,  no exactly 1 child!";
        return NULL;
    }
    return dynamic_cast<AbstractElement*>(parent->itemAt(0));
}


