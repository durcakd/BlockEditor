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

void Item::keyPressEvent ( QKeyEvent * event )
{
    //if (!+Qt::ControlModifier & event->modifiers()) {
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
    // qDebug() << "";
    //qDebug() << "start " << linePos << "  " << getType() << "  " << toPlainText();
    // left
    while( NULL != targed) {
        AbstractElement *parrent = targed->getLayoutParrent();
        if( NULL != parrent && OrientationEnum::vertical == parrent->styleE()->getOrientation()) {
            break;
        }
        while ( NULL != targed->nextPrevius(false)) {
            targed = targed->nextPrevius(false);
            linePos += targed->textLength();
            //qDebug() << " + "<< targed->textLength() << " = " << linePos << "    " << targed->getType();
        }

        //qDebug() << "up parrent "<< targed->getType() << "  " << targed->textE();
        targed = parrent;

    }
    // down/up


    if (NULL!= targed) {qDebug() << "1. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();}
    while (NULL != targed && NULL == targed->nextPrevius(down)) {  // there can be more vertical
        targed = targed->getLayoutParrent();
        //if (NULL!= targed) {qDebug() << "2. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();}
    }
    if (NULL == targed) { return; }
    targed = targed->nextPrevius(down);


    //qDebug() << "3. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();
    // right
    int tlen;
    while (targed->isLayoutE()) {
        //qDebug() << "down child    " << targed->getType();
        bool isHorizontal = OrientationEnum::horizontal == targed->styleE()->getOrientation();

        Layout *lay = dynamic_cast <Layout*>(targed);
        targed = dynamic_cast<AbstractElement*>(lay->itemAt(0)); // TODO no children?

        tlen = targed->textLength();
        while (isHorizontal
               && tlen < linePos
               && NULL != targed->nextPrevius(true)) {
            qDebug() << " - "<< tlen << " = " << linePos << "    " << targed->getType();
            targed = targed->nextPrevius(true);
            linePos -= (tlen);
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
void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MOUSE PRESS EVENT";
    BlockScene *scene = BlockScene::instance();
    if(!_selectedE) {
        _selectedE = this;

    }
    if(scene->selectedLeaf() != this) {
        qDebug() << "new selected";
        if(scene->selectedLeaf()) {
            scene->paintedElemement()->setPaintEnable(false);
            dynamic_cast<QGraphicsItem*>(scene->paintedElemement())->update();
        }
        scene->setSelectedE(this, _selectedE);
    }
    QGraphicsTextItem::mousePressEvent(event);

}


void Item::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (Qt::ControlModifier & event->modifiers()) {
        qDebug() << "ctrl wheel ";

        if(!_selectedE) {
            _selectedE = this;
        }
        BlockScene *scene = BlockScene::instance();
        if(scene->selectedLeaf() != this) {
            qDebug() << "new selected";
            if(scene->selectedLeaf()) {
                scene->paintedElemement()->setPaintEnable(false);
                dynamic_cast<QGraphicsItem*>(scene->paintedElemement())->update();
            }
        }

        if( event->delta() > 0) {  // UP
            AbstractElement *parentE = dynamic_cast<AbstractElement*>(_selectedE->getLayoutParrent());
            if(parentE) {
                parentE->setPaintEnable(true);
                _selectedE->setPaintEnable(false);
                dynamic_cast<QGraphicsItem*>(parentE)->update();
                dynamic_cast<QGraphicsItem*>(_selectedE)->update();
                _selectedE = parentE;
                scene->setSelectedE(this, _selectedE);
            }

        } else {  // DOWN
            AbstractElement *child = this;
            AbstractElement *parentE = dynamic_cast<AbstractElement*>(getLayoutParrent());
            while(parentE) {
                if (parentE == _selectedE) {
                    _selectedE->setPaintEnable(false);
                    child->setPaintEnable(true);
                    dynamic_cast<QGraphicsItem*>(child)->update();
                    dynamic_cast<QGraphicsItem*>(_selectedE)->update();
                    _selectedE = child;
                    scene->setSelectedE(this, _selectedE);
                    break;
                }
                child = parentE;
                parentE = dynamic_cast<AbstractElement*>( parentE->getLayoutParrent());
            }
        }
    }

    event->accept();
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
