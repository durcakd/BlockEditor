#include "item/state/elementstable.h"
#include <QDebug>


ElementStable::ElementStable()
    : ElementState()
{

}

bool ElementStable::isSpaced() const {
    return true;
}
