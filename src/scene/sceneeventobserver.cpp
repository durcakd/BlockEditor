#include "scene/sceneeventobserver.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

SceneEventObserver::SceneEventObserver(QGraphicsItem *parent)
    : QGraphicsItem(parent) {

}


bool SceneEventObserver::sceneEventFilter ( QGraphicsItem * watched, QEvent *event ) {

    else if (event->type() == QEvent::GraphicsSceneWheel) {
        //QGraphicsSceneMouseEvent * mp = static_cast<QGraphicsSceneMouseEvent *>(event);
        qDebug() << "SEFO  MOUSE wheel EVENT";
        return true;
    }

    if (event->type() == QEvent::GraphicsSceneMousePress) {
        //QGraphicsSceneMouseEvent * mp = static_cast<QGraphicsSceneMouseEvent *>(event);
        qDebug() << "SEFO  MOUSE press EVENT";
        return true;
    }

    else if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        //QGraphicsSceneMouseEvent * mp = static_cast<QGraphicsSceneMouseEvent *>(event);
        qDebug() << "SEFO  MOUSE release EVENT";
        return true;
    }

    else if (event->type() == QEvent::GraphicsSceneMouseMove) {
        //QGraphicsSceneMouseEvent * mp = static_cast<QGraphicsSceneMouseEvent *>(event);
        qDebug() << "SEFO  MOUSE move EVENT";
        return true;
    }

    else if (event->type() == QEvent::GraphicsSceneDragEnter) {
        //QGraphicsSceneMouseEvent * mp = static_cast<QGraphicsSceneMouseEvent *>(event);
        qDebug() << "SEFO  MOUSE drag enter EVENT";
        return true;
    }
    else if (event->type() == QEvent::GraphicsSceneDragLeave) {
        //QGraphicsSceneMouseEvent * mp = static_cast<QGraphicsSceneMouseEvent *>(event);
        qDebug() << "SEFO  MOUSE drag leave EVENT";
        return true;
    }
    else if (event->type() == QEvent::GraphicsSceneDrop) {
        qDebug() << "SEFO  MOUSE drop EVENT";
        return true;
    }

    else if (event->type() == QEvent::KeyPress) {
        //QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event) ;
        qDebug() << "SEFO KEY press EVENT";
        return true;
    }
    return false;
}
