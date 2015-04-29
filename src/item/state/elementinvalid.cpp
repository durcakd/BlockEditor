#include "item/state/elementinvalid.h"
#include <QDebug>

#include "item/state/elementchanged.h"
#include "item/abstractelement.h"
#include "item/item.h"

ElementInvalid::ElementInvalid()
    : ElementState()
{

}

bool ElementInvalid::isSpaced() const {
    return false;
}


void ElementInvalid::entry(AbstractElement *element) const {
    Item *item = dynamic_cast<Item*>(element);
    if (item) {
        item->setDefaultTextColor(Qt::red);
    }
}

void ElementInvalid::exit(AbstractElement *element) const {

}

void ElementInvalid::edited(AbstractElement *element) const {
    element->setState( new ElementChanged);
}
