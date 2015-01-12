#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsTextItem>
#include <QSizeF>


class QGraphicsLinearLayout;
class Style;
class Layout;

class AbstractElement {
public:
    explicit AbstractElement(QString type, Style *style, QGraphicsLinearLayout *layoutParrent = 0);

    QString getType() const;
    Layout *getLayoutParrent() const;
    AbstractElement *getNext() const { return _next; }
    AbstractElement *getPrevius() const { return _previous; }
    void setNext(AbstractElement *next) { _next = next; }
    void setPrevius(AbstractElement *previous) { _previous = previous; }
    void setParrentE(Layout *parrent) { _layoutParrentor = parrent; }

    virtual QSizeF elementSizeHint(Qt::SizeHint which) const = 0;
    virtual bool isLayoutE() const = 0;


protected:
    QString _type;
    bool _elementType;
    Style *_style;
    Layout *_layoutParrentor;
    AbstractElement *_next;
    AbstractElement *_previous;

};

#endif
