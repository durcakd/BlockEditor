#ifndef WRITEITEMCOMMAND_H
#define WRITEITEMCOMMAND_H


#include "scene/command/command.h"

class QGraphicsItem;
class Item;

class WriteItemCommand : public Command {
public:
    explicit WriteItemCommand(QGraphicsItem *watched, int pos, int charsRemoved, int charsAdded);

    void execute();
    void undo();

protected:
    //void horCursorMovement(QTextCursor &cursor, bool toNext);
    //void verCursorMovement(QTextCursor &cursor, bool down);

    Item *_item;
    int pos;
    int charsRemoved;
    int charsAdded;



};

#endif
