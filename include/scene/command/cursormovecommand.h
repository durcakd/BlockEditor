#ifndef CURSORMOVECOMMAND_H
#define CURSORMOVECOMMAND_H


#include "scene/command/command.h"

class QGraphicsItem;
class QKeyEvent;
class Item;

class CursorMoveCommand : public Command {
public:
    explicit CursorMoveCommand(QGraphicsItem *watched, QKeyEvent *event);

    void execute();
    void undo();

protected:
    void horCursorMovement(QTextCursor &cursor, bool toNext);
    void verCursorMovement(QTextCursor &cursor, bool down);

    Item *_item;
    QKeyEvent *_event;



};

#endif
