#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsLinearLayout>
#include <QSizeF>
#include <QList>
#include <QObject>

#include "abstractelement.h"

class Style;

class Layout : public QObject, public QGraphicsLinearLayout, public AbstractElement
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

    QGraphicsLayoutItem  *firstLastItem(bool first) const;

public slots:

    void childItemChanged();

protected:




    QString _layoutType;
    //QList<AbstractElement*> _childLayouts;


};

#endif
