#ifndef ELEMENTCHANGED_H
#define ELEMENTCHANGED_H

#include "item/state/elementstate.h"

class ElementChanged : public ElementState
{

public:
    explicit ElementChanged();

    bool isSpaced() const;


};

#endif
