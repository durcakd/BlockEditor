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
    explicit Item(Layout *parent = 0, QString text = "");

    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    QSizeF elementSizeHint(Qt::SizeHint which) const;
    int textLength(bool length = true) const;
    QString textE() const;

    void setStyleE(Style *style);

    QTextDocument *_document;
    bool isLayoutE() const;

    QString getText() const {return _text;}
    QString textOnLineForPos(int pos, bool toRight) const;
    QPixmap toPixmap();

public slots:

    void textChanged( int pos, int charsRemoved, int charsAdded);

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
