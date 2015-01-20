#include "scene/layout.h"
#include "style/style.h"
#include <QDebug>



Layout::Layout(QString type, Style *style, QGraphicsLayoutItem *parent)
    : QObject(),
      QGraphicsLinearLayout( parent),
      AbstractElement(type, style, dynamic_cast<QGraphicsLinearLayout*>(parent)),
      QGraphicsRectItem(0,15,100,10, dynamic_cast<QGraphicsItem*>(parent))
{
    //qDebug() << "---------   "<< type << " " << style;
    if (OrientationEnum::horizontal == _style->getOrientation()) {
        this->setOrientation( Qt::Horizontal);
    } else {
        this->setOrientation( Qt::Vertical);
    }
    //_childLayouts = new  QList<Layout*>();
    setInstantInvalidatePropagation(true);
    //setSpacing(0);
    //setContentsMargins(0, 0, 0, 0);

//    QSizePolicy sp = sizePolicy();
//        sp.setHeightForWidth(true);
//        setSizePolicy(sp);
    //QGraphicsRectItem::

}


void Layout::childItemChanged() {
    this->updateGeometry();
}






QSizeF Layout::elementSizeHint(Qt::SizeHint which) const
{
    return sizeHint(which);
}

void printG(const QRectF &geom) {
    qDebug() << "  g: " << geom;
    qDebug() << "     " << geom.center();
}

void Layout::setGeometry(const QRectF &geom)
{
    qreal left, top, right, bottom;
    QRectF zgeom = geom;
    QRectF zbound = boundingRect();
    QRectF zgeometry = geometry();

    prepareGeometryChange();
    QGraphicsLinearLayout::setGeometry( geom);

   /*taking the geometry*/
   //QRectF effectiveRect = geometry();
   getContentsMargins(&left, &top, &right, &bottom);

   /*adjust margins*/
   //effectiveRect.adjust(+left, +top, -right, -bottom);


  // qDebug()<<"   "<<left<<","<<top<<","<<right<<","<<bottom;
   //setPos(geom.topLeft());
   setPos(geom.topLeft());
   setPos(0,0);

   /*
    if(getLayoutParrent()){
        getLayoutParrent()->getContentsMargins(&left, &top, &right, &bottom);
        QRectF geom2 = geom;
        //geom2.moveTopLeft(QPointF(left, top));

        setPos(geom2.topLeft() - getLayoutParrent()->pos());
        //setPos(geom2.topLeft());
    }else{
        setPos(geom.topLeft());
    }


    qDebug() << "-------" << getType() << "  " << textE();
    qDebug() << "  g : " << boundingRect();
    qDebug() << "  g : " << geom;
    qDebug() << "  g : " << pos();
    qDebug() << "  c : " << left << " " << top << " " << right << " " << bottom;
    //qDebug() << "  g: " << pos();
    //qDebug() << "  g: " << scenePos();


    QRectF geom2 = geom;
    geom2.moveTopLeft(QPointF(left, top));


    QGraphicsLinearLayout::setGeometry( geom);
    qDebug() << "  b : " << boundingRect();

//    qDebug() << ">-----" << getType() << "  " << textE();
//    qDebug() << "  l  " << QGraphicsLinearLayout::geometry();
    //qDebug() << "  g: " << pos();
    //qDebug() << "  g: " << scenePos();

*/
   QString parentType= "";
   if(getLayoutParrent()) {
      parentType = getLayoutParrent()->getType();
   }
   qDebug() << ">>>>>> " << getType() << "   " << parentType << "  " << textE();
   //qDebug() << "  marg  "<<left<<","<<top<<","<<right<<","<<bottom;
   //qDebug() << "  geom  " << zgeom;
   qDebug() << "< geom  " << geom;
   //qDebug() << "  boud  " << boundingRect();
   //qDebug() << "< boud  " << zbound;
   //qDebug() << "  gmet  " << zgeometry;
   //qDebug() << "< gmet  " << geometry();
   qDebug() << "<<<<<" << getType() << "  " << textE();

}

QRectF Layout::boundingRect() const
{
    //return   QGraphicsRectItem::boundingRect();
    //return   QGraphicsLinearLayout::boundingRect();
    return QRectF(QPointF(0,0), QGraphicsLinearLayout::geometry().size());
}
/*
QRectF Layout::geometry() const {
    //return QRectF(0,0,0,0);
    return boundingRect();
}
*/

void Layout::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    //QString parentType= "";
    //if(getLayoutParrent()) {
    //   parentType = getLayoutParrent()->getType();
    //}
    //qDebug() << "PAINT  " << getType() << "   " << parentType << "  " << textE();
    //qDebug() << "     g  " << geometry();
    //qDebug() << "     p  " << pos();
    //qDebug() << "     sp " << scenePos();

    //QRectF frame(QPointF(0,0), geometry().size());
    QRectF frame(geometry());
    frame.translate(4,20);
     painter->drawRoundedRect(frame, 3.0, 3.0);
     //QGraphicsRectItem::paint(painter, option, widget);
}

QSizeF Layout::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    //return  QGraphicsLinearLayout::sizeHint(which);
    return  QGraphicsLinearLayout::sizeHint(which);
    //return  QGraphicsRectItem::sizeHint(which);

    //return
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
