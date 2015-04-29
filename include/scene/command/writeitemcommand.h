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
    void undoSimpleAddition();
    void simpleAdditionInStartOrEnd(QChar newChar, bool inStart);

    Item *createItemForInsert(QChar newChar);
    Item *createItemForInsert(bool stable, QString text);

    Item *_item;
    int pos;
    int charsRemoved;
    int charsAdded;



};

#endif
