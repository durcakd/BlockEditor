#include "scene/command/moveelementcommand.h"
#include <QDebug>


#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>


//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"
//#include "scene/blockscene.h"
//#include "scene/scenestate.h"
//#include "item/item.h"


MoveElementCommand::MoveElementCommand(QGraphicsItem *watched, QGraphicsSceneMouseEvent *event)
    : Command()
{
    _event = event;
    //_item = dynamic_cast<Item *>(watched) ;


}


void MoveElementCommand::execute() {
    qDebug() << "EXE moveElementCommand";

    //SceneState *state = BlockScene::instance()->getSceneState();

}



