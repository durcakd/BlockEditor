#include "item/state/elementchanged.h"
#include <QDebug>

#include "item/abstractelement.h"
#include "item/item.h"
#include "item/layout.h"
#include "style/style.h"
#include "scene/parser.h"
#include "scene/blockscene.h"
#include "item/state/elementvalid.h"
#include "item/state/elementinvalid.h"

ElementChanged::ElementChanged()
    : ElementState()
{

}

bool ElementChanged::isSpaced() const {
    return false;
}

void ElementChanged::entry(AbstractElement *element) const {
    handleChange(element);

}

void ElementChanged::exit(AbstractElement *element) const {
    qDebug() << "changed exit: ";
    Item *item = dynamic_cast<Item*>(element);
    if (item) {
        if (element->styleE()->getIsColor()) {
            item->setDefaultTextColor(Qt::blue);
        } else {
            item->setDefaultTextColor(Qt::black);
        }
    }
}

void ElementChanged::edited(AbstractElement *element) const {
    handleChange(element);
}

void ElementChanged::handleChange(AbstractElement *element) const {
    Item *item = dynamic_cast<Item*>(element);
    if (item) {
        item->setDefaultTextColor(Qt::gray);
    }
    bool ok;

    Layout *parent = element->getLayoutParrent();
    qDebug() << "1. "<<parent->textE();
    while (parent != NULL && parent->textE().length() == element->textE().length()) {
        parent = parent->getLayoutParrent();
        qDebug() << "2. "<<parent->textE();

    }
    AbstractElement *p = parent;
    if (p == NULL) {
        qDebug() << " zeby root";

        p = element;
    }
    qDebug() << "3. "<<p->textE();


    ok = Parser::instance()->reparse(p->textE());
    if (!ok) {qDebug() << "Reparsing parent error";}
    if (ok) {qDebug() << "Reparsing parent ok";}
    //ok = Parser::instance()->reparse(BlockScene::instance()->root()->textE());
    //if (!ok) {qDebug() << "Reparsing error";}

    if (ok) {
        element->setState( new ElementValid);
    } else {
        element->setState( new ElementInvalid);
    }
}
