#include "item/state/elementvalid.h"
#include <QDebug>

#include "item/abstractelement.h"

ElementValid::ElementValid()
    : ElementState()
{

}


bool ElementValid::isSpaced() const {
    return false;
}


void ElementValid::entry(AbstractElement *element) const {

}

void ElementValid::exit(AbstractElement *element) const {

}
