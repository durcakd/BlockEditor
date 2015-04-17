#include "scene/command/changemarkedcommand.h"
#include <QDebug>


#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>

//#include "item/item.h"
//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"


ChangeMarkedCommand::ChangeMarkedCommand(QGraphicsItem *watched, QGraphicsSceneWheelEvent *event)
    : Command()
{
    _event = event;
    //_item = static_cast<Item *>(watched) ;


}


void ChangeMarkedCommand::execute() {
    qDebug() << "EXE changeMarkedCommand";

}



