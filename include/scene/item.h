#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsLayoutItem>
#include <QSizeF>

#include "scene/abstractelement.h"

class Item : public QGraphicsLayoutItem, public QGraphicsTextItem, public AbstractElement
{
public:
    explicit Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);

    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    QSizeF elementSizeHint(Qt::SizeHint which) const;

protected:
    QString _text;
};

#endif
