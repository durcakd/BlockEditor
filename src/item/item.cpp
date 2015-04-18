#include "item/item.h"
#include <QDebug>
#include <QFontMetrics>
#include <QTextDocument>
#include <QTextCursor>
#include <QMimeData>
#include <QDrag>
#include <QFontDatabase>

#include <QGraphicsLinearLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneWheelEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QDrag>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QWidget>
#include <QStyle>
#include <QApplication>
#include <item/layout.h>
#include "style/style.h"
#include "scene/blockscene.h"


#include "scene/mimedata.h"



Item::Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent)
    :  QGraphicsLayoutItem(parent), QGraphicsTextItem(), AbstractElement(type, style, parent)
{
    //_text = text.trimmed();
    _text = text;


    _document = this->document();
    _document->setPlainText(_text);
    setTextInteractionFlags( Qt::TextEditorInteraction);

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);

    if (style->getIsColor()){
        setDefaultTextColor(Qt::blue);
    }
    // draging
    setAcceptDrops(true);
    //color = QColor(Qt::lightGray);
    _selectedE = NULL;


    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    setFont(fixedFont);

QConnect:connect( _document, &QTextDocument::contentsChanged, this , &Item::textUpdatedSlot );

    // setGeometry();
}

void Item::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QStyleOptionGraphicsItem *o = const_cast<QStyleOptionGraphicsItem*>(option);
    o->state &= ~QStyle::State_HasFocus;
    o->state &= ~QStyle::State_Selected;
    QGraphicsTextItem::paint(painter, o, widget);
}

void Item::setGeometry(const QRectF &geom) {

    //qDebug() << "GG" << geom.size().width() <<"  "<< geom.size().height() << _type ;
    //qDebug() << "  " << geom.topLeft().x() <<"  "<< geom.topLeft().y();
    //qDebug() << "  " << geom.topLeft().x() <<"  "<< geom.topLeft().y()+boundingRect().size().width();
    //prepareGeometryChange();
    //QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.bottomLeft());

}

void Item::textUpdatedSlot() {
    updateGeometry();
    getLayoutParrent()->invalidate();
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

bool Item::isLayoutE() const
{
    return false;
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



void Item::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

    const MimeData *md = dynamic_cast<const MimeData*>(event->mimeData());
    if ( md && md->hasElement()) {
        //Item *item = dynamic_cast<Item *>(md->element());
        //qDebug() << "drag " << item->toPlainText() << " "  << item;
        qDebug() << "drag " << toPlainText();


        event->setAccepted(true);
        dragOver = true;
        update();
    } else {
        event->setAccepted(false);
    }
}

void Item::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;

    update();

}

void Item::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    const MimeData *md = dynamic_cast<const MimeData*>(event->mimeData());
    if ( md && md->hasElement()) {
        qDebug() << "drop 1 ";
        AbstractElement *item = dynamic_cast<AbstractElement *>(md->element());
        qDebug() << "drop 2" << item->textE() << " "  << item;


        // remove from old position

        // TODO item parrent can be null -> null pointer exception
        item->getLayoutParrent()->removeItem(dynamic_cast<QGraphicsLayoutItem*>(item));
        item->getLayoutParrent()->invalidate();  // TODO remove maybe
        //item->getLayoutParrent()->updateGeometry();
        //item->getLayoutParrent()->getLayoutParrent()->invalidate();
        //item->getLayoutParrent()->getLayoutParrent()->updateGeometry();

        //item->getLayoutParrent()->setGeometry();
        if( item->getNext()) {
            item->getNext()->setPrevius(item->getPrevius());
        }
        if( item->getPrevius()) {
            item->getPrevius()->setNext(item->getNext());
        }
        // insert to new position
        Layout *parrent = dynamic_cast <Layout*>( getLayoutParrent());
        if(parrent) {
            item->setLayoutParrent(parrent);
            //item->setParentLayoutItem(parrent);
            int index = parrent->indexOf(this);
            parrent->insertItem(index+1,dynamic_cast<QGraphicsLayoutItem*>(item));


            item->setNext(getNext());
            item->setPrevius(this);
            if( getNext()) {
                getNext()->setPrevius(item);
            }
            setNext(item);

            //parrent->updateGeometry();
        }

        event->setDropAction(Qt::MoveAction);
        event->accept();
        // event->acceptProposedAction();
    }
    update();

}


// ---------------
void Item::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QGraphicsTextItem::mouseReleaseEvent(event);
}

void Item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance()) {
        return;
    }

    //qDebug() << "et " << event->widget()->s;
    qDebug() << "this " << toPlainText() << " "  << this;


    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new MimeData(_selectedE);
    drag->setMimeData(mime);



    mime->setColorData(color);
    mime->setText(QString("#%1%2%3")
                  .arg(color.red(), 2, 16, QLatin1Char('0'))
                  .arg(color.green(), 2, 16, QLatin1Char('0'))
                  .arg(color.blue(), 2, 16, QLatin1Char('0')));



    QPixmap pixmap(5, 5);
    pixmap.fill(Qt::green);

    QPainter painter(&pixmap);
    painter.translate(15, 15);
    painter.end();

    //    pixmap.setMask(pixmap.createHeuristicMask());

    drag->setPixmap(pixmap);
    Layout *parrent = this->getLayoutParrent();

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

    if (dropAction == Qt::MoveAction) {
        qDebug() << "move exec done";
        //this->setVisible(false);
        if(parrent) {
            //parrent->updateGeometry();
        }
    }


    setCursor(Qt::ArrowCursor);
    // QGraphicsTextItem::mouseMoveEvent(event);
}

