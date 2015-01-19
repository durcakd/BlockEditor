#ifndef RECTITEMLAYOUT_H
#define RECTITEMLAYOUT_H

#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QGraphicsRectItem>

#include "scene/layout.h"
#include "scene/abstractelement.h"

#include <QSizeF>


//class QGraphicsSceneDragDropEvent;
//class QGraphicsSceneMouseEvent;



class RectLayout :
        public QGraphicsRectItem,
        public QGraphicsLinearLayout
{

public:
    explicit RectLayout(qreal x, qreal y, qreal h, qreal w, QGraphicsLayoutItem *parent = 0);

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;


public slots:

protected:

private:

};


#endif
