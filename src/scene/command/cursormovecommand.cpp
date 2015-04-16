#include "scene/command/cursormovecommand.h"


#include <QDebug>
#include <QKeyEvent>
//#include <QGraphicsItem>
#include <QTextCursor>
#include "QGraphicsLayoutItem"

#include "item/item.h"
#include "item/layout.h"


CursorMoveCommand::CursorMoveCommand(QGraphicsItem *watched, QKeyEvent *event)
    : Command()
{
    _item = static_cast<Item *>(watched) ;
    _event = event;

}


void CursorMoveCommand::execute() {
    qDebug() << "EXE cursorMoveCommand";

    QTextCursor cursor = _item->textCursor();
    switch (_event->key()){

    case Qt::Key_Left:
        horCursorMovement(cursor, false);
        break;
    case Qt::Key_Right:
        horCursorMovement(cursor, true);
        break;
//    case Qt::Key_Up:
//        verCursorMovement(cursor, false);
//        break;
//    case Qt::Key_Down:
//        verCursorMovement(cursor, true);
//        break;
    }
}


void CursorMoveCommand::horCursorMovement(QTextCursor &cursor, bool toNext)
{
    AbstractElement *targed;
    if (_item->textLength(toNext) == cursor.position()) {
        targed = _item->nextPrevius(toNext);
        if (NULL == targed) {
            targed = _item->getLayoutParrent();
            while (NULL != targed && NULL == targed->nextPrevius(toNext)) {
                targed = targed->getLayoutParrent();
            }
            if (NULL == targed) {
                return;
            }
            targed = targed->nextPrevius(toNext);
        }
        while (targed->isLayoutE()) {
            Layout *lay = dynamic_cast <Layout*>(targed);
            QGraphicsLayoutItem  *layout = lay->firstLastItem(toNext);
            targed = dynamic_cast <AbstractElement*>(layout);

        }
        Item *ite = dynamic_cast <Item*>(targed);
        ite->setFocus();
        cursor = ite->textCursor();
        cursor.setPosition(ite->textLength(!toNext));
        ite->setTextCursor(cursor);

    } else {
        if(toNext){
            cursor.movePosition(QTextCursor::NextCharacter);
        } else {
            cursor.movePosition(QTextCursor::PreviousCharacter);
        }
        _item->setTextCursor(cursor);
    }
}
