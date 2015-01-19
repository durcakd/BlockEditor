#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsLinearLayout>
#include <QSizeF>
#include <QList>
#include <QObject>

#include "abstractelement.h"
#include <QGraphicsItem>

class Style;

class Layout :
        public QObject,
        public AbstractElement,
        public QGraphicsRectItem,
        public QGraphicsLinearLayout
{
    Q_OBJECT

public:
    explicit Layout(QString type, Style *style, QGraphicsLayoutItem *parent = 0);

    QSizeF elementSizeHint(Qt::SizeHint which) const;

    //QSizeF childrenSizeHint(Qt::SizeHint which) const;
    //QList<AbstractElement*> getChildLayouts() const;
    //void addLayoutChild(AbstractElement *child);
    void updateChildNeighbors();
    bool isLayoutE() const;
    int textLength(bool length) const;
    QString textE() const;

    int indexOf(AbstractElement *element);

    QGraphicsLayoutItem  *firstLastItem(bool first) const;


    // TODO setContentsMargins();
    // TODO getContentsMargins();
    // TODO setItemSpacing()

    // Inherited from QGraphicsItem
    //QRectF boundingRect() const;

    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;



public slots:

    void childItemChanged();

protected:




    QString _layoutType;
    //QList<AbstractElement*> _childLayouts;


};

#endif
