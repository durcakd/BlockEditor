#ifndef REPARSER_H
#define REPARSER_H

#include "scene/elementobserver.h"

class AbstractElement;


class Reparser : public ElementObserver{
public:
    explicit Reparser();

    void update(AbstractElement *element);

};

#endif
