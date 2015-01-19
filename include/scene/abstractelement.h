#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsTextItem>
#include <QSizeF>

class Style;
class Layout;
class QGraphicsLinearLayout;

class AbstractElement
{
public:
    explicit AbstractElement(QString type, Style *style, QGraphicsLinearLayout *layoutParrent = 0);

    QString getType() const;
    Layout *getLayoutParrent() const;
    void setLayoutParrent(Layout *parrent) {_layoutParrentor = parrent;}

    AbstractElement *getNext() const { return _next; }
    AbstractElement *getPrevius() const { return _previous; }
    AbstractElement *nextPrevius(bool next) const;
    void setNext(AbstractElement *next) { _next = next; }
    void setPrevius(AbstractElement *previous) { _previous = previous; }
    void setParrentE(Layout *parrent) { _layoutParrentor = parrent; }
    Style *styleE() const {return _style;}

    virtual QSizeF elementSizeHint(Qt::SizeHint which) const = 0;
    virtual bool isLayoutE() const = 0;
    virtual int textLength(bool length = true) const = 0;
    virtual QString textE() const = 0;


protected:
    QString _type;
    bool _elementType;
    Style *_style;
    Layout *_layoutParrentor;
    AbstractElement *_next;
    AbstractElement *_previous;

};

#endif
