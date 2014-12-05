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

    _document = new QTextDocument();

    QTextCursor cursor = QTextCursor(_document);
    cursor.insertText( _text);
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
    //qDebug() << "basicBlock.sizeHint" << boundingRect().size().width() << "  " << boundingRect().size().height() << _type;
    //qDebug() << "basicBlock.sizeHint" << fm.width(toPlainText()) << "  " << fm.height();

    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
    case Qt::MaximumSize:
        //return this->boundingRect().size();
        return QSize(fm.width(toPlainText()), fm.height());
    }
    return this->boundingRect().size();
    //return constraint;
}


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
