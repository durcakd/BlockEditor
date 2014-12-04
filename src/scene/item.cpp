#include "scene/item.h"
#include <QDebug>
#include <QFontMetrics>
#include <QTextDocument>
#include <QTextCursor>

#include <QGraphicsLinearLayout>

Item::Item(QString type, QString text, QGraphicsLinearLayout *parent)
    : QGraphicsLayoutItem(parent), QGraphicsTextItem(), AbstractElement(type, parent)
{
    _text = text;

    QTextDocument *document = new QTextDocument();

    QTextCursor cursor = QTextCursor(document);
    cursor.insertText( _text);
    setDocument(document);
    setTextInteractionFlags( Qt::TextEditable);


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

