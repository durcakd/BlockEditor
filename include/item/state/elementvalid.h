#ifndef ELEMENTVALID_H
#define ELEMENTVALID_H

#include "item/state/elementstate.h"

class AbstractElement;

class ElementValid : public ElementState
{

public:
    explicit ElementValid();

    void entry(AbstractElement *element) const;
    void exit(AbstractElement *element) const;
    bool isSpaced() const;

};

#endif
