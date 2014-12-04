#include "scene/abstractelement.h"
#include <QDebug>

#include <QGraphicsLinearLayout>

AbstractElement::AbstractElement(QString type, QGraphicsLinearLayout *layoutParrent)
{
    _type = type;
    _layoutParrentor = layoutParrent;
}

QString AbstractElement::getType() const
{
    return _type;
}

QGraphicsLinearLayout* AbstractElement::getLayoutParrent() const
{
    return _layoutParrentor;
}
