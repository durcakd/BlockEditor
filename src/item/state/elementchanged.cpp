#include "item/state/elementchanged.h"
#include <QDebug>

#include "item/abstractelement.h"
#include "item/item.h"
#include "style/style.h"

ElementChanged::ElementChanged()
    : ElementState()
{

}

bool ElementChanged::isSpaced() const {
    return false;
}

void ElementChanged::entry(AbstractElement *element) const {

    Item *item = dynamic_cast<Item*>(element);
    if (item) {
        item->setDefaultTextColor(Qt::red);
    }
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
