#ifndef ELEMENTINVALID_H
#define ELEMENTINVALID_H

#include "item/state/elementstate.h"

class ElementInvalid : public ElementState
{

public:
    explicit ElementInvalid();

    bool isSpaced() const;

};

#endif
