#include "scene/command/changemarkedcommand.h"
#include <QDebug>


#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>

#include "item/item.h"
#include "scene/scenestate.h"
#include "scene/blockscene.h"
//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"


ChangeMarkedCommand::ChangeMarkedCommand(QGraphicsItem *watched, QGraphicsSceneWheelEvent *event)
    : Command()
{
    _event = event;
    _item = static_cast<Item *>(watched) ;


}


void ChangeMarkedCommand::execute() {
    qDebug() << "EXE changeMarkedCommand";


    if (Qt::ControlModifier & _event->modifiers()) {
        qDebug() << "ctrl wheel ";

        SceneState *state = BlockScene::instance()->getSceneState();


        if (_item != state->getSelectedItem()) {
            qDebug() << "new selected";
            if(state->getPaintedElement()) {
                state->getPaintedElement()->setPaintEnable(false);
            }
            state->setSelectedItem(_item);  //
            state->setPaintedElement(_item);  //
        }

        AbstractElement *oldPainted = state->getPaintedElement();

        if( _event->delta() > 0) {  // UP
            AbstractElement *parentE = dynamic_cast<AbstractElement*>(oldPainted->getLayoutParrent());
            if(parentE) {
                parentE->setPaintEnable(true);
                oldPainted->setPaintEnable(false);
                state->setPaintedElement( parentE);
            }

        } else {  // DOWN
            AbstractElement *child = _item;
            AbstractElement *parentE = dynamic_cast<AbstractElement*>(_item->getLayoutParrent());
            while(parentE) {
                if (parentE == oldPainted) {
                    oldPainted->setPaintEnable(false);
                    child->setPaintEnable(true);
                    state->setPaintedElement(child);
                    break;
                }
                child = parentE;
                parentE = dynamic_cast<AbstractElement*>( parentE->getLayoutParrent());
            }
        }
    }

}



