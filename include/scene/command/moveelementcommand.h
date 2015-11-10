#ifndef MOVEELEMENTCOMMAND_H
#define MOVEELEMENTCOMMAND_H


#include "scene/command/command.h"


class QGraphicsSceneMouseEvent;
class QGraphicsItem;
class Item;


class MoveElementCommand : public Command {
public:
    explicit MoveElementCommand(QGraphicsItem *watched, QGraphicsSceneMouseEvent *event);

    void execute();

protected:


   QGraphicsSceneMouseEvent *_event;
   Item *_item;



};

#endif
