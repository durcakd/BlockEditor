#include "item/state/elementinvalid.h"
#include <QDebug>


ElementInvalid::ElementInvalid()
    : ElementState()
{

}

bool ElementInvalid::isSpaced() const {
    return false;
}
