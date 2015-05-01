#ifndef CURSORMOVECOMMAND_H
#define CURSORMOVECOMMAND_H


#include "scene/command/command.h"

class QGraphicsItem;
class QKeyEvent;
class Item;
class AbstractElement;

class CursorMoveCommand : public Command {
public:
    explicit CursorMoveCommand(QGraphicsItem *watched, QKeyEvent *event);

    void execute();
    void undo();

protected:
    void horCursorMovement(QTextCursor &cursor, bool toNext);
    void verCursorMovement(QTextCursor &cursor, bool down);
    void verCursorMovement2(QTextCursor &cursor, bool down);
    int skipChild(AbstractElement *child, int linePos);

    Item *_item;
    QKeyEvent *_event;



};

#endif
