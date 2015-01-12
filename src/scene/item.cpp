#include "scene/item.h"
#include <QDebug>
#include <QFontMetrics>
#include <QTextDocument>
#include <QTextCursor>
#include <QMimeData>
#include <QDrag>

#include <QGraphicsLinearLayout>
#include <QGraphicsSceneMouseEvent>
#include <scene/layout.h>

Item::Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent)
    :  QGraphicsLayoutItem(parent), QGraphicsTextItem(), AbstractElement(type, style, parent)
{
    _text = text.trimmed();

    _document = new QTextDocument(_text);
    setDocument(_document);
    setTextInteractionFlags( Qt::TextEditable);

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setAcceptDrops(true);

QConnect:connect( _document, &QTextDocument::contentsChanged, this , &Item::textUpdatedSlot );

    // setGeometry();
}
void Item::setGeometry(const QRectF &geom) {

    //qDebug() << "GG" << geom.size().width() <<"  "<< geom.size().height() << _type ;
    //qDebug() << "  " << geom.topLeft().x() <<"  "<< geom.topLeft().y();
    //qDebug() << "  " << geom.topLeft().x() <<"  "<< geom.topLeft().y()+boundingRect().size().width();
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.bottomLeft());

}

void Item::textUpdatedSlot() {
    updateGeometry();

}

QSizeF Item::elementSizeHint(Qt::SizeHint which) const
{
    return sizeHint(which);
}


QSizeF Item::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    QFontMetrics fm(font());
    QString text = toPlainText();
    //text.
    //qDebug() << "basicBlock.sizeHint" << boundingRect().size().width() << "  " << boundingRect().size().height() << _type;
    //qDebug() << "basicBlock.sizeHint" << fm.width(toPlainText()) << "  " << fm.height();

    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
    case Qt::MaximumSize:
        //return this->boundingRect().size();
        return QSize(fm.width(text), fm.height());
    }
    return this->boundingRect().size();
    //return constraint;
}

void Item::keyPressEvent ( QKeyEvent * event )
{
    AbstractElement *targed;
    QTextCursor cursor = textCursor();

    switch (event->key()){

    case Qt::Key_Left:
        if (0 == cursor.position()) {

            qDebug() << "0 from left";
            targed = getPrevius();
            if (NULL == targed) {
                targed = getLayoutParrent();
                qDebug() << "1.p     " << targed;
                while (NULL != targed && NULL == targed->getPrevius()) {
                    targed = targed->getLayoutParrent();
                    qDebug() << "n.p     " << targed;
                    if (targed != NULL) {
                        qDebug() << "targed U " << targed << "   " << targed->getType() << "  " << targed->isLayoutE();}
                }
                if (NULL == targed) {
                    return;
                }
                targed = targed->getPrevius();
            }
            while (targed->isLayoutE()) {
                if (targed != NULL) {
                    qDebug() << "targed D " << targed << "   " << targed->getType() << "  " << targed->isLayoutE();}

                Layout *lay = dynamic_cast <Layout*>(targed);
                QGraphicsLayoutItem  *layout = lay->itemAt(lay->count()-1);
                targed = dynamic_cast <AbstractElement*>(layout);

            }
            if (targed != NULL) {
                qDebug() << "targed F " << targed << "   " << targed->getType() << "  " << targed->isLayoutE();}

            Item *ite = dynamic_cast <Item*>(targed);
            //ite->setActive(true);

            ite->setFocus();
            cursor = ite->textCursor();
            cursor.setPosition(ite->toPlainText().length());
            ite->setTextCursor(cursor);




        } else {
            cursor.movePosition(QTextCursor::PreviousCharacter);
            setTextCursor(cursor);
        }



        break;
    case Qt::Key_Right:
        cursor.movePosition(QTextCursor::NextCharacter);
        setTextCursor(cursor);
        break;
    case Qt::Key_Up:
        //qDebug() << "  UP cursor";
        qDebug() << "me       " << this;
        if (getPrevius() != NULL) {
            qDebug() << "previous " << getPrevius() << "   " << getPrevius()->getType() << "  " << getPrevius()->isLayoutE();}
        if (getNext() != NULL) {
            qDebug() << "next     " << getNext() << "   " << getNext()->getType() << "  " << getNext()->isLayoutE();}
    case Qt::Key_Down:
        qDebug() << "  DOWN cursor";
        break;
    default:
        QGraphicsTextItem::keyPressEvent(event);
    }
}

bool Item::isLayoutE() const
{
    return false;
}

/*
void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        //mimeData->setText("commentEdit->toPlainText()");
        //mimeData->setColorData(QColor(Qt::green));
        drag->setMimeData(mimeData);
        //drag->setPixmap(iconPixmap);

        Qt::DropAction dropAction = drag->exec();

    } else {
        QGraphicsTextItem::mousePressEvent(event);
    }

}
*/
