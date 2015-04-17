#include "scene/command/selectitemcommand.h"
#include <QDebug>


#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>


//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"
#include "scene/blockscene.h"
#include "scene/scenestate.h"
#include "item/item.h"


SelectItemCommand::SelectItemCommand(QGraphicsItem *watched, QGraphicsSceneMouseEvent *event)
    : Command()
{
    _event = event;
    _item = static_cast<Item *>(watched) ;


}


void SelectItemCommand::execute() {
    qDebug() << "EXE selectItemCommand";

    SceneState *state = BlockScene::instance()->getSceneState();

    if (_item != state->getSelectedItem()) {
        qDebug() << "new selected";
        if(state->getPaintedElement()) {
            state->getPaintedElement()->setPaintEnable(false);
        }
        state->setSelectedItem(_item);
        state->setPaintedElement(_item);   // TODO selected
    }
    _item->mousePressEvent(_event);

}



