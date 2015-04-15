#ifndef CURSORMOVECOMMAND_H
#define CURSORMOVECOMMAND_H


#include "scene/command/command.h"


class CursorMoveCommand : public Command {
public:
    explicit CursorMoveCommand();

    void execute();

protected:

};

#endif
