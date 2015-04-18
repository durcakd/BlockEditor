#include "scene/command/moveelementcommand.h"
#include <QDebug>


#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>


//#include "item/layout.h"
//#include "item/abstractelement.h"
//#include "style/style.h"
#include "scene/blockscene.h"
#include "scene/scenestate.h"
#include "item/item.h"
#include "scene/mimedata.h"
//#include <QLine>


MoveElementCommand::MoveElementCommand(QGraphicsItem *watched, QGraphicsSceneMouseEvent *event)
    : Command()
{
    _event = event;
    _item = dynamic_cast<Item *>(watched) ;
}


void MoveElementCommand::execute() {
    qDebug() << "EXE moveElementCommand";

    SceneState *state = BlockScene::instance()->getSceneState();


    if (QLineF(_event->screenPos(), _event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance()) {
        return;
    }

    //qDebug() << "et " << event->widget()->s;
    qDebug() << "this " << _item->toPlainText();


    QDrag *drag = new QDrag(_event->widget());
    QMimeData *mime = new MimeData( state->getPaintedElement());
    drag->setMimeData(mime);



    //mime->setColorData(color);
    mime->setText("textdata");



    QPixmap pixmap(5, 5);
    pixmap.fill(Qt::green);

    QPainter painter(&pixmap);
    painter.translate(15, 15);
    painter.end();

    //    pixmap.setMask(pixmap.createHeuristicMask());

    drag->setPixmap(pixmap);
    Layout *parrent = _item->getLayoutParrent();

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

    if (dropAction == Qt::MoveAction) {
        qDebug() << "move exec done";
        //this->setVisible(false);
        if(parrent) {
            //parrent->updateGeometry();
        }
    }


    //setCursor(Qt::ArrowCursor);


}



