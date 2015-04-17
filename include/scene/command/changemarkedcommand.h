#ifndef CHANGEMARKEDCOMMAND_H
#define CHANGEMARKEDCOMMAND_H


#include "scene/command/command.h"


class QGraphicsSceneWheelEvent;
class QGraphicsItem;


class ChangeMarkedCommand : public Command {
public:
    explicit ChangeMarkedCommand(QGraphicsItem *watched, QGraphicsSceneWheelEvent *event);

    void execute();

protected:


   QGraphicsSceneWheelEvent *_event;
   //Item *_item;



};

#endif
