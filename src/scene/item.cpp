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
#include "style/style.h"

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
        horCursorMovement(cursor, false);
        break;

    case Qt::Key_Right:
        horCursorMovement(cursor, true);
        break;

    case Qt::Key_Up:
        verCursorMovement(cursor, false);
        break;

    case Qt::Key_Down:
        verCursorMovement(cursor, true);
        break;

    default:
        QGraphicsTextItem::keyPressEvent(event);
    }
}

bool Item::isLayoutE() const
{
    return false;
}

void Item::horCursorMovement(QTextCursor &cursor, bool toNext)
{
    AbstractElement *targed;
    if (textLength(toNext) == cursor.position()) {
        targed = nextPrevius(toNext);
        if (NULL == targed) {
            targed = getLayoutParrent();
            while (NULL != targed && NULL == targed->nextPrevius(toNext)) {
                targed = targed->getLayoutParrent();
            }
            if (NULL == targed) {
                return;
            }
            targed = targed->nextPrevius(toNext);
        }
        while (targed->isLayoutE()) {
            Layout *lay = dynamic_cast <Layout*>(targed);
            QGraphicsLayoutItem  *layout = lay->firstLastItem(toNext);
            targed = dynamic_cast <AbstractElement*>(layout);

        }
        Item *ite = dynamic_cast <Item*>(targed);
        ite->setFocus();
        cursor = ite->textCursor();
        cursor.setPosition(ite->textLength(!toNext));
        ite->setTextCursor(cursor);

    } else {
        if(toNext){
            cursor.movePosition(QTextCursor::NextCharacter);
        } else {
            cursor.movePosition(QTextCursor::PreviousCharacter);
        }
        setTextCursor(cursor);
    }
}

void Item::verCursorMovement(QTextCursor &cursor, bool down) {
    AbstractElement *targed = this;
    int linePos = cursor.position();
    qDebug() << "";
    qDebug() << "start " << linePos << "  " << getType() << "  " << toPlainText();
    // left
    /*do {

        while ( NULL != targed->nextPrevius(false)) {
            targed = targed->nextPrevius(false);
            linePos += targed->textLength();
            qDebug() << " + "<< targed->textLength() << " = " << linePos << "    " << targed->getType();
        }
        if(NULL == targed->getLayoutParrent()) { return; }
        targed = targed->getLayoutParrent();
        qDebug() << "up parrent "<< targed->getType() << "  " << targed->textE();



    } while (OrientationEnum::vertical != targed->styleE()->getOrientation());
    */


    while( NULL != targed) {
        AbstractElement *parrent = targed->getLayoutParrent();
        if( NULL != parrent && OrientationEnum::vertical == parrent->styleE()->getOrientation()) {
            break;
        }
        while ( NULL != targed->nextPrevius(false)) {
            targed = targed->nextPrevius(false);
            linePos += targed->textLength();
            qDebug() << " + "<< targed->textLength() << " = " << linePos << "    " << targed->getType();
        }

        qDebug() << "up parrent "<< targed->getType() << "  " << targed->textE();
        targed = parrent;

    }
    // down/up


    if (NULL!= targed) {qDebug() << "1. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();}
    while (NULL != targed && NULL == targed->nextPrevius(down)) {  // there can be more vertical
        targed = targed->getLayoutParrent();
        if (NULL!= targed) {qDebug() << "2. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();}
    }
    if (NULL == targed) { return; }
    targed = targed->nextPrevius(down);


    qDebug() << "3. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();
    // right
    int tlen;
    while (targed->isLayoutE()) {
        qDebug() << "down child    " << targed->getType();
        bool isHorizontal = OrientationEnum::horizontal == targed->styleE()->getOrientation();

        Layout *lay = dynamic_cast <Layout*>(targed);
        targed = dynamic_cast<AbstractElement*>(lay->itemAt(0)); // TODO no children?

        tlen = targed->textLength();
        while (isHorizontal
               && tlen < linePos
               && NULL != targed->nextPrevius(true)) {
            qDebug() << " - "<< tlen << " = " << linePos << "    " << targed->getType();
            targed = targed->nextPrevius(true);
            linePos -= tlen;
            tlen = targed->textLength();
        }
    }


    Item *ite = dynamic_cast <Item*>(targed);
    qDebug() << "final:" << targed->getType() << "  " << ite->toPlainText();
    ite->setFocus();
    cursor = ite->textCursor();
    tlen = targed->textLength();
    linePos = linePos < tlen ? linePos : tlen;
    cursor.setPosition(linePos);
    ite->setTextCursor(cursor);
}

int Item::textLength(bool length) const
{
    if(length) {
        return toPlainText().length();
    } else {
        return 0;
    }
}

QString Item::textE() const
{
    return toPlainText();
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
