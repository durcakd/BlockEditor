#include "item/state/elementvalid.h"
#include <QDebug>


ElementValid::ElementValid()
    : ElementState()
{

}


bool ElementValid::isSpaced() const {
    return false;
}
