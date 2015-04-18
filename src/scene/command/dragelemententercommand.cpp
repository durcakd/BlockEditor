#include "scene/command/dragelemententercommand.h"
#include <QDebug>


#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>


//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"
//#include "scene/blockscene.h"
//#include "scene/scenestate.h"
//#include "item/item.h"


DragElementEnterCommand::DragElementEnterCommand(QGraphicsItem *watched, QGraphicsSceneDragDropEvent *event)
    : Command()
{
    _event = event;
    //_item = dynamic_cast<Item *>(watched) ;


}


void DragElementEnterCommand::execute() {
    qDebug() << "EXE dragElementEnterCommand";

    //SceneState *state = BlockScene::instance()->getSceneState();

}



