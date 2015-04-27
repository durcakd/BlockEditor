#ifndef ELEMENTVALID_H
#define ELEMENTVALID_H

#include "item/state/elementstate.h"

class ElementValid : public ElementState
{

public:
    explicit ElementValid();

    bool isSpaced() const;



};

#endif
