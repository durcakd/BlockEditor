#include "scene/abstractelement.h"
#include <QDebug>

#include <QGraphicsLinearLayout>

AbstractElement::AbstractElement(QString type, Style *style, QGraphicsLinearLayout *layoutParrent)
{
    _type = type;
    _layoutParrentor = layoutParrent;
    _style = style;
}

QString AbstractElement::getType() const
{
    return _type;
}

QGraphicsLinearLayout* AbstractElement::getLayoutParrent() const
{
    return _layoutParrentor;
}
