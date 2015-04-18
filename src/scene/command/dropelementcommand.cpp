#include "scene/command/dropelementcommand.h"
#include <QDebug>


#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>


//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"
//#include "scene/blockscene.h"
//#include "scene/scenestate.h"
//#include "item/item.h"


DropElementCommand::DropElementCommand(QGraphicsItem *watched, QGraphicsSceneDragDropEvent *event)
    : Command()
{
    _event = event;
    //_item = dynamic_cast<Item *>(watched) ;


}


void DropElementCommand::execute() {
    qDebug() << "EXE dropElementCommand";

    //SceneState *state = BlockScene::instance()->getSceneState();

}



