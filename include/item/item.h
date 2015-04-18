#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsLayoutItem>
#include <QSizeF>
#include <QObject>

#include "item/abstractelement.h"

//class QGraphicsSceneDragDropEvent;
//class QGraphicsSceneMouseEvent;



class Item :   public QGraphicsLayoutItem, public QGraphicsTextItem, public AbstractElement
{

public:
    explicit Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);

    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    QSizeF elementSizeHint(Qt::SizeHint which) const;
    int textLength(bool length = true) const;
    QString textE() const;

    QTextDocument *_document;
    bool isLayoutE() const;

    QString getText() const {return _text;}

public slots:
    void textUpdatedSlot();

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;


protected:




    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    QString _text;
    QColor color;

private:

};


#endif
