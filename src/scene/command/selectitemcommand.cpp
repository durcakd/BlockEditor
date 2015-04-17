#include "scene/command/selectitemcommand.h"
#include <QDebug>


#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

//#include "item/item.h"
//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"


SelectItemCommand::SelectItemCommand(QGraphicsItem *watched, QGraphicsSceneMouseEvent *event)
    : Command()
{
    _event = event;
    //_item = static_cast<Item *>(watched) ;


}


void SelectItemCommand::execute() {
    qDebug() << "EXE selectItemCommand";

}



