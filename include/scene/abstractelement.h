#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsTextItem>
#include <QSizeF>

class QGraphicsLinearLayout;

class AbstractElement
{
public:
    explicit AbstractElement(QString type, QGraphicsLinearLayout *layoutParrent = 0);

    QString getType() const;
    QGraphicsLinearLayout *getLayoutParrent() const;

    virtual QSizeF elementSizeHint(Qt::SizeHint which) const = 0;



protected:
    QString _type;
    bool _elementType;
    QGraphicsLinearLayout *_layoutParrentor;
};

#endif
