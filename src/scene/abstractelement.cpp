#include "scene/abstractelement.h"
#include "scene/layout.h"
#include <QDebug>

#include <QGraphicsLinearLayout>

class Layout;

AbstractElement::AbstractElement(QString type, Style *style, QGraphicsLinearLayout *layoutParrent)
{
    _type = type;
    _layoutParrentor = static_cast<Layout*>(layoutParrent);
    _style = style;
    _next = NULL;
    _previous = NULL;
    _enablePaint = false;
}

QString AbstractElement::getType() const
{
    return _type;
}

Layout* AbstractElement::getLayoutParrent() const
{
    return _layoutParrentor;
}

AbstractElement *AbstractElement::nextPrevius(bool next) const {
    if(next) {
        //qDebug() << "next";
        return getNext();
    } else {
        //qDebug() << "previous";
        return getPrevius();
    }
}

QString AbstractElement::toString() const
{
    QString parentType= "";
    if(getLayoutParrent()) {
       parentType = getLayoutParrent()->getType();
    }
    return getType() + "   " + parentType + "  " + textE();
}
