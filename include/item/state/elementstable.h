#ifndef ELEMENTSTABLE_H
#define ELEMENTSTABLE_H

#include "item/state/elementstate.h"

class AbstractElement;

class ElementStable : public ElementState
{

public:
    explicit ElementStable();

    void entry(AbstractElement *element) const;
    void exit(AbstractElement *element) const;
    bool isSpaced() const;



};

#endif
