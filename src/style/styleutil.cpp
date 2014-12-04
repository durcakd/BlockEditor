#include "style/styleutil.h"
#include <QDebug>

#include <QGraphicsLinearLayout>

#include "style/style.h"

StyleUtil::StyleUtil()
{

}

Style* StyleUtil::getStyle(QString type) const
{
    Style *style = _styleMap.value(type);
    // TODO
    return style;
}

void StyleUtil::addStyle( Style *style) {
    qDebug() << "Inserted style: " << style->getStyleType() << " " << style;
    _styleMap.insert(style->getStyleType(), style);
}
