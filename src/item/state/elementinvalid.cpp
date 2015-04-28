#include "item/state/elementinvalid.h"
#include <QDebug>


ElementInvalid::ElementInvalid()
    : ElementState()
{

}

bool ElementInvalid::isSpaced() const {
    return false;
}


void ElementInvalid::entry(AbstractElement *element) const {

}

void ElementInvalid::exit(AbstractElement *element) const {

}
