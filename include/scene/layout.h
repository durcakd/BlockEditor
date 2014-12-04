#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsLinearLayout>
#include <QSizeF>
#include <QList>

#include "abstractelement.h"

class Layout : public QGraphicsLinearLayout, public AbstractElement
{
public:
    explicit Layout(QString type, QGraphicsLayoutItem *parent = 0);

    QSizeF elementSizeHint(Qt::SizeHint which) const;

    QSizeF childrenSizeHint(Qt::SizeHint which) const;
    QList<AbstractElement*> getChildLayouts() const;
    void addLayoutChild(AbstractElement *child);


protected:
    QString _layoutType;
    QList<AbstractElement*> _childLayouts;

};

#endif
