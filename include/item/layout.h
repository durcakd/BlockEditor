#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsLinearLayout>
#include <QGraphicsItem>
#include <QSizeF>
#include <QList>
#include <QObject>
#include <QPainter>

#include "abstractelement.h"

class Style;

class Layout :
        public QObject,
        public QGraphicsLinearLayout,
        public AbstractElement,
        public QGraphicsItem
{
    Q_OBJECT

public:

    explicit Layout(QGraphicsLayoutItem *parent = 0);

    explicit Layout(QString type, Style *style, QGraphicsLayoutItem *parent = 0);

    QSizeF elementSizeHint(Qt::SizeHint which) const;

    //QSizeF childrenSizeHint(Qt::SizeHint which) const;
    //QList<AbstractElement*> getChildLayouts() const;
    //void addLayoutChild(AbstractElement *child);
    void updateChildNeighbors();
    bool isLayoutE() const;
    int textLength(bool length) const;
    QString textE() const;
    void setStyleE(Style *style);

    int indexOf(AbstractElement *element);

    void insertBehind( AbstractElement *oldElement, AbstractElement *newElement);
    void insertBefore( AbstractElement *oldElement, AbstractElement *newElement);


    QGraphicsLayoutItem  *firstLastChildrenElement(bool first) const;


    void setGeometry(const QRectF &geom);

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    // Inherited from AbstractElement
    void setPaintEnable( bool enablePaint );

    // Inherited from QGraphicsItem
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/) Q_DECL_OVERRIDE;
    QPixmap toPixmap();

public slots:

    void childItemChanged();

protected:

    QString _layoutType;
    //QList<AbstractElement*> _childLayouts;

};

#endif
