#include "scene/layout.h"
#include <QDebug>


Layout::Layout(QString type, QGraphicsLayoutItem *parent)
    : QGraphicsLinearLayout( parent), AbstractElement(type, dynamic_cast<QGraphicsLinearLayout*>(parent))
{

    this->setOrientation( Qt::Vertical);
    //_childLayouts = new  QList<Layout*>();
    // setGeometry();
}



QSizeF Layout::childrenSizeHint(Qt::SizeHint which) const
{
    //qDebug() << "childrenSizeHint";
    qreal h = 0, w = 0;
    foreach (AbstractElement* child, _childLayouts) {
        QSizeF size = child->elementSizeHint(which);
        if( Qt::Vertical == orientation()) {
           h += size.height();
           w = w < size.width() ? size.width() : w;
        } else {
            w += size.width();
            h = h < size.height() ? size.height() : h;
        }

    }
    //qDebug() <<"CHSH  "<< w << "  " << h;
    return QSizeF(w,h);
}

QList<AbstractElement *> Layout::getChildLayouts() const
{
    return _childLayouts;
}

void Layout::addLayoutChild(AbstractElement *child)
{
    _childLayouts.append(child);
}
QSizeF Layout::elementSizeHint(Qt::SizeHint which) const
{
    return sizeHint(which);
}
