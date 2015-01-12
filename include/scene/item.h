#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsLayoutItem>
#include <QSizeF>
#include <QObject>

#include "scene/abstractelement.h"

class Item :   public QGraphicsLayoutItem, public QGraphicsTextItem, public AbstractElement
{

public:
    explicit Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);

    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    QSizeF elementSizeHint(Qt::SizeHint which) const;

    QTextDocument *_document;
    bool isLayoutE() const;

    QString getText() const {return _text;}


public slots:
    void textUpdatedSlot();

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent ( QKeyEvent * event );

protected:
    QString _text;
};

#endif
