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

    bool hasSpace(const QString str) const;

    void simpleAddition();
    void complexAddition();

    Item *_item;
    int pos;
    int charsRemoved;
    int charsAdded;



};

#endif
