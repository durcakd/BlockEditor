#include "item/blankitem.h"
#include "style/styleutil.h"

BlankItem::BlankItem(QString type, QString text, Style *, QGraphicsLinearLayout *parent)
    :  Item(type, text, StyleUtil::instance()->getStyle("spaced_text"), parent)
{

}


bool BlankItem::isSpaceItem() const {
    return true;
}
