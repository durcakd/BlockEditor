#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsTextItem>
#include <QSizeF>


class QGraphicsLinearLayout;
class Style;

class AbstractElement
{
public:
    explicit AbstractElement(QString type, Style *style, QGraphicsLinearLayout *layoutParrent = 0);

    QString getType() const;
    QGraphicsLinearLayout *getLayoutParrent() const;

    virtual QSizeF elementSizeHint(Qt::SizeHint which) const = 0;



protected:
    QString _type;
    bool _elementType;
    Style *_style;
    QGraphicsLinearLayout *_layoutParrentor;
};

#endif
