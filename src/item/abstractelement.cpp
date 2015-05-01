#include "item/abstractelement.h"

#include "item/layout.h"
#include "item/state/elementstate.h"
#include <QDebug>

#include <QGraphicsLinearLayout>

class Layout;

AbstractElement::AbstractElement(QGraphicsLinearLayout *layoutParrent)
{
    _layoutParrentor = static_cast<Layout*>(layoutParrent);
    _next = NULL;
    _previous = NULL;
    _enablePaint = false;
    _state = NULL;
}

QString AbstractElement::getType() const
{
    return _type;
}

void AbstractElement::setState(ElementState *state) {
    if (_state != NULL) {
        state->exit(this);
    }
    _state = state;
    _state->entry(this);
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

AbstractElement *AbstractElement::nextPreviousAlsoHor(bool toNext) {

    const AbstractElement *element = this;
    Layout *parent = element->getLayoutParrent();

    while (parent != NULL && parent->orientation() == Qt::Horizontal) {
        if (NULL != element->nextPrevius(toNext)) {
            return firstLastItemOf( element->nextPrevius(toNext), toNext);
        }
        element = parent;
        parent = element->getLayoutParrent();
    }
    return NULL;
}

AbstractElement *AbstractElement::nextPreviousAlsoVert(bool toNext) {
    const AbstractElement *element = this;
    do {
       if (NULL != element->nextPrevius(toNext)) {
           return firstLastItemOf( element->nextPrevius(toNext), toNext);
       }
       element = element->getLayoutParrent();
    } while (element != NULL);
    return NULL;
}

AbstractElement *AbstractElement::firstLastItemOf(AbstractElement *parent, bool first) {
    if (parent == NULL) {
        return NULL;
    }
    return parent->firstLastItem(first);
}

AbstractElement *AbstractElement::firstLastItem(bool first) {
    AbstractElement *targed = this;
    while (targed->isLayoutE()) {
        Layout *lay = dynamic_cast <Layout*>(targed);
        QGraphicsLayoutItem  *layout = lay->firstLastChildrenElement(first);
        targed = dynamic_cast <AbstractElement*>(layout);
    }
    return targed;
}


bool AbstractElement::isParent(AbstractElement *checkedParent) {
    AbstractElement *parent = dynamic_cast<AbstractElement*>(this->getLayoutParrent());
    while (parent) {
        if (parent == checkedParent) {
            return true;
        }
        parent = dynamic_cast<AbstractElement*>( parent->getLayoutParrent());
    }
    return false;
}

QString AbstractElement::toString() const
{
    QString parentType= "";
    if(getLayoutParrent()) {
       parentType = getLayoutParrent()->getType();
    }
    return getType() + "   " + parentType + "  " + textE();
}
