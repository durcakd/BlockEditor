#ifndef WRITEITEMCOMMAND_H
#define WRITEITEMCOMMAND_H


#include "scene/command/command.h"

class QGraphicsItem;
class AbstractElement;
class Item;
class Layout;

class WriteItemCommand : public Command {
public:
    explicit WriteItemCommand(QGraphicsItem *watched, int pos, int charsRemoved, int charsAdded);

    void execute();
    void undo();

protected:

    bool hasSpace(const QString str) const;

    void simpleAddition();
    void simpleRemove();
    void complexAddition();
    void undoSimpleAddition();
    void simpleAdditionStartEnd(QChar newChar, bool inStart);
    void simpleAdditionMiddle(QChar newChar);
    void simpleAdditionEnter();

    AbstractElement *getParsable(Item *item) const;
    //AbstractElement *WriteItemCommand::getParsable(Item *left, Item *right, Item *focused) const;
    AbstractElement *getParsableForRemoved(AbstractElement *toRemove, Item *focusItem) const;

    AbstractElement *findInsteadtoSelect();
    Item *createItemForInsert(QChar newChar);
    Item *createItemForInsert(bool stable, QString text);
    Item *createItemForInsert(bool stable, QString text, Layout *parent);


    Item *_item;
    int pos;
    int charsRemoved;
    int charsAdded;



};

#endif
