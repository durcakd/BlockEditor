#ifndef REPARSER_H
#define REPARSER_H

#include "scene/elementobserver.h"

class AbstractElement;
class Layout;

class Reparser : public ElementObserver{
public:
    explicit Reparser();
    ~Reparser();

    void update(AbstractElement *element);

    Layout *findBiggerParnet(AbstractElement *element);
    AbstractElement *firstChild(Layout *parent);
    AbstractElement *firstChild(AbstractElement *parent);
    void replaceElement(AbstractElement *oldElem, AbstractElement*newElem);

    void reparse(AbstractElement *element);


    int     cursorAbsolutePosition(AbstractElement *topParent, AbstractElement *focused) const;
    void    setSursorPosition(AbstractElement *topParent, int pos) const;
    int     skipChild(AbstractElement *child, int pos) const;

private:
    AbstractElement *_chandedElement;

};

#endif
