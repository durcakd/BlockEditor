#include "scene/rectitemlayout.h"
#include <QDebug>

#include <QPainter>
#include <QWidget>
#include <QApplication>



RectLayout::RectLayout(qreal x, qreal y, qreal h, qreal w , QGraphicsLayoutItem *parent)
    : QGraphicsLinearLayout(parent),
      QGraphicsRectItem(x, y, h, w, dynamic_cast<QGraphicsItem*>(parent))
{

    //setFlag(ItemIsMovable);
    //setFlag(ItemSendsGeometryChanges);
    //setFlag(ItemIsSelectable);
    // draging
    //setAcceptDrops(true);

}

void RectLayout::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF RectLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
        // Do not allow a size smaller than the pixmap with two frames around it.
        return QSize(12, 12);
    case Qt::MaximumSize:
        return QSizeF(1000,1000);
    default:
        break;
    }
    return constraint;
}
