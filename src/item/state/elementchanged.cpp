#include "item/state/elementchanged.h"
#include <QDebug>


ElementChanged::ElementChanged()
    : ElementState()
{

}

bool ElementChanged::isSpaced() const {
    return false;
}
