#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsTextItem>
#include <QSizeF>


class QGraphicsLinearLayout;
class Style;
class Layout;
class ElementState;

class AbstractElement {

public:
    explicit AbstractElement(QGraphicsLinearLayout *layoutParrent);

    QString getType() const;
    void setType(QString type) {_type = type;}
    Layout *getLayoutParrent() const;
    void setLayoutParrent(Layout *parrent) {_layoutParrentor = parrent;}

    AbstractElement *getNext() const { return _next; }
    AbstractElement *getPrevius() const { return _previous; }
    AbstractElement *nextPrevius(bool next) const;
    AbstractElement *nextPreviousAlsoHor(bool toNext);
    AbstractElement *nextPreviousAlsoVert(bool toNext);
    AbstractElement *firstLastItem(bool first);
    AbstractElement *firstLastItemOf(AbstractElement *parent, bool first);


    void setNext(AbstractElement *next) { _next = next; }
    void setPrevius(AbstractElement *previous) { _previous = previous; }
    //void setParrentE(Layout *parrent) { _layoutParrentor = parrent; }
    Style *styleE() const {return _style;}
    virtual void setStyleE(Style *style) { _style = style;}

    ElementState *state() const {return _state;}
    void setState(ElementState *state);

    bool isPaintEnabled() const {return _enablePaint;}
    bool isParent(AbstractElement *checkedParent);

    virtual void setPaintEnable( bool enablePaint ) { _enablePaint = enablePaint;}


    virtual QSizeF elementSizeHint(Qt::SizeHint which) const = 0;
    virtual bool isLayoutE() const = 0;
    virtual int textLength(bool length = true) const = 0;
    virtual QString textE() const = 0;


    virtual QPixmap toPixmap() = 0;


    QString toString() const;

protected:
    QString _type;
    bool _elementType;
    Style *_style;
    ElementState *_state;

    Layout *_layoutParrentor;
    AbstractElement *_next;
    AbstractElement *_previous;
    bool _enablePaint;

};

#endif
