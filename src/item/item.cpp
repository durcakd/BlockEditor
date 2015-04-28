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
#include <QWidget>
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
#include "scene/command/writeitemcommand.h"


#include "scene/mimedata.h"


Item::Item(Layout *parent, QString text)
    : QGraphicsLayoutItem(parent),
      QGraphicsTextItem(dynamic_cast<QGraphicsItem*>(parent)),
      AbstractElement(parent)
{
    _text = text;


    _document = this->document();
    _document->setPlainText(_text);
    setTextInteractionFlags( Qt::TextEditorInteraction);

    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);


    // draging
    setAcceptDrops(true);

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    setFont(fixedFont);

connect( _document, &QTextDocument::contentsChange, this , &Item::textChanged );

    // setGeometry();
}

void Item::setStyleE(Style *style) {
    AbstractElement::setStyleE(style);

    if (style->getIsColor()){
        setDefaultTextColor(Qt::blue);
    }
}


Item::Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent)
    :  QGraphicsLayoutItem(parent), QGraphicsTextItem(dynamic_cast<QGraphicsItem*>(parent)), AbstractElement(type, style, parent)
{
    //_text = text.trimmed();
    _text = text;


    _document = this->document();
    _document->setPlainText(_text);
    setTextInteractionFlags( Qt::TextEditorInteraction);

    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);

    if (style->getIsColor()){
        setDefaultTextColor(Qt::blue);
    }
    // draging
    setAcceptDrops(true);
    //color = QColor(Qt::lightGray);



    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    setFont(fixedFont);

connect( _document, &QTextDocument::contentsChange, this , &Item::textChanged );


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


void Item::textChanged(int pos, int charsRemoved, int charsAdded) {
    if (charsRemoved!=charsAdded){
        BlockScene::instance()->addCommand(new WriteItemCommand(this, pos, charsRemoved, charsAdded));
    }
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




// ---------------
void Item::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QGraphicsTextItem::mouseReleaseEvent(event);
}

QPixmap Item::toPixmap() {
    QSizeF elementSize = elementSizeHint(Qt::MinimumSize);
    QPixmap pixmap(elementSize.width()+3, elementSize.height()+3);
    pixmap.fill(QColor(0,0,0,10));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(-2, -3);

    QStyleOptionGraphicsItem opt;
    QWidget wid;
    paint(&painter, &opt, &wid);

    QRectF rect(3,3,elementSize.width(),elementSize.height());
    painter.drawRoundedRect(rect, 3.0, 3.0);

    painter.end();
    return pixmap;
}
