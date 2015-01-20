#include "scene/layout.h"
#include "style/style.h"
#include <QDebug>



Layout::Layout(QString type, Style *style, QGraphicsLayoutItem *parent)
    : QObject(),
      QGraphicsLinearLayout( parent),
      AbstractElement(type, style, dynamic_cast<QGraphicsLinearLayout*>(parent)),
      QGraphicsItem(dynamic_cast<QGraphicsItem*>(parent))
{
    //qDebug() << "---------   "<< type << " " << style;
    if (OrientationEnum::horizontal == _style->getOrientation()) {
        this->setOrientation( Qt::Horizontal);
    } else {
        this->setOrientation( Qt::Vertical);
    }
    //_childLayouts = new  QList<Layout*>();
    setInstantInvalidatePropagation(true);
    setVisible(false);

}


void Layout::childItemChanged() {
    this->updateGeometry();
}

QSizeF Layout::elementSizeHint(Qt::SizeHint which) const
{
    return sizeHint(which);
}


// **************************************************
// redefine QGRaphics rectangular method

QSizeF Layout::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    return  QGraphicsLinearLayout::sizeHint(which);
}

void Layout::setGeometry(const QRectF &geom)
{    
   prepareGeometryChange();
   QGraphicsLinearLayout::setGeometry( geom);
   setPos(0,0);
}

QRectF Layout::boundingRect() const
{
    return QRectF(QPointF(0,0), QGraphicsLinearLayout::geometry().size());
}

void Layout::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF frame(geometry());
    frame.translate(3,20);
    frame.adjust(-5,-5,3,3);

    painter->drawRoundedRect(frame, 3.0, 3.0);
}

void Layout::updateChildNeighbors()
{
    qDebug() << "  chids: " << count();
    AbstractElement *previous = NULL;
    for (int i=0; i < count(); i++) {
        if (AbstractElement *myItem = dynamic_cast <AbstractElement*>(itemAt(i))) {
            //if(NULL == previous) { qDebug() << "NULL           " << myItem;}
            //else { qDebug() << previous << "    " << myItem;}

            if( NULL != previous ) {
                previous->setNext(myItem);
            }
            myItem->setPrevius(previous);
            previous = myItem;

            // recursively update children
            if (Layout *layout = dynamic_cast <Layout*>(itemAt(i))) {
                layout->updateChildNeighbors();
            }
        }
    }

    qDebug() << " Neighbors controll:";

    qDebug() << "  chids: " << count();
    for (int i=0; i < count(); i++) {
        if (AbstractElement *myItem = dynamic_cast <AbstractElement*>(itemAt(i))) {
            if (myItem->getPrevius() != NULL) {
                qDebug() << "previous " << myItem->getPrevius() << "   " << myItem->getPrevius()->getType() << "  " << myItem->getPrevius()->isLayoutE();}
            if (myItem->getNext() != NULL) {
                qDebug() << "next     " << myItem->getNext() << "   " << myItem->getNext()->getType() << "  " << myItem->getNext()->isLayoutE();}

        }
    }
    //qDebug() << "THIS  " << this << "   " << this->getType();
    if( this->getLayoutParrent() != NULL){
        //qDebug() << "THIS  " << this->getLayoutParrent();
    }
    qDebug() << "";
}

bool Layout::isLayoutE() const
{
    return true;
}

QGraphicsLayoutItem  *Layout::firstLastItem(bool first) const
{
    if (first) {
        return itemAt(0);
    } else {
        return itemAt(count()-1);
    }
}

int Layout::textLength(bool length) const
{
    if(length) {
        int sum = 0;
        for ( int i=0; i < count(); i++) {
            if (AbstractElement *element = dynamic_cast <AbstractElement*>(itemAt(i))) {
                sum += element->textLength(length);
            }
        }
        return sum;
    } else {
        return 0;
    }
}

QString Layout::textE() const
{
    QString text;
    for ( int i=0; i < count(); i++) {
        if (AbstractElement *element = dynamic_cast <AbstractElement*>(itemAt(i))) {
            text += element->textE();
        }
    }
    return text;
}

int Layout::indexOf(AbstractElement *element)
{
    for ( int i=0; i < count(); i++) {
        if (dynamic_cast <AbstractElement*>(itemAt(i)) == element) {
            return i;
        }
    }
    return -1;
}

/*
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

void Layout::addLayoutChild(AbstractElement *child)
{
    _childLayouts.append(child);
}

QList<AbstractElement *> Layout::getChildLayouts() const
{
    return _childLayouts;
}
*/
