#include "scene/command/cursormovecommand.h"


#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>
#include "QGraphicsLayoutItem"

#include "item/item.h"
#include "item/layout.h"
#include "item/abstractelement.h"
#include "style/style.h"


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
    case Qt::Key_Up:
        verCursorMovement(cursor, false);
        break;
    case Qt::Key_Down:
        verCursorMovement(cursor, true);
        break;
    }
}


void CursorMoveCommand::horCursorMovement(QTextCursor &cursor, bool toNext)
{
    AbstractElement *targed;
    if (_item->textLength(toNext) == cursor.position()) {
        targed = _item->nextPreviousAlsoVert(toNext);
        if (NULL == targed) {
            return;
        }

        Item *ite = dynamic_cast <Item*>(targed);
        ite->setFocus();
        cursor = ite->textCursor();
        cursor.setPosition(ite->textLength(!toNext));
        ite->setTextCursor(cursor);

    } else {
        if(toNext){
            cursor.movePosition(QTextCursor::NextCharacter);//, QTextCursor::KeepAnchor);
        } else {
            cursor.movePosition(QTextCursor::PreviousCharacter);//, QTextCursor::KeepAnchor);
        }
        _item->setTextCursor(cursor);
    }
}

void CursorMoveCommand::verCursorMovement(QTextCursor &cursor, bool down) {
    int linePos = cursor.position();

    Layout *parent = _item->getLayoutParrent();
    const AbstractElement *element = _item;

    //qDebug() << "calculate position on line";
    // calculate position on line
    while (parent != NULL
           && ( Qt::Horizontal == parent->orientation()
                || (Qt::Vertical == parent->orientation() && element->nextPrevius(down) == NULL))) {

        if (Qt::Vertical != parent->orientation()) {
            AbstractElement *neighbor = element->getPrevius();
            while (neighbor) {
                linePos += neighbor->textLength();
                neighbor = neighbor->getPrevius();
            }
        }
        element = parent;
        parent = parent->getLayoutParrent();
    }

    if (parent == NULL) {
        qDebug() << "WARNING!!! vertical cursor movement 1, parent=NULL";
        return;
    }



    // TODO this could be removed >>
    // find vertical , that has neighbors
    while (NULL != parent && NULL == element->nextPrevius(down)) {  // there can be more vertical
        //qDebug() << "  - vertical wrong parent: "<< parent->getType()  << "  " << parent->textE();
        element = parent;
        parent = parent->getLayoutParrent();
    }
    if (parent == NULL) {
        qDebug() << "WARNING!!! vertical cursor movement 2, parent=NULL";
        return;
    }
    // TODO << below could be removed maybe



    //qDebug() << "Up/Down";
    AbstractElement *targed = element->nextPrevius(down);
    AbstractElement *child = NULL;

    // find position on new line
    //qDebug() << "find position on new line   linePos= "  << linePos;
    //qDebug() << "----- new targed: "<< targed->getType()  << "  " << targed->textE();
    while (targed->isLayoutE()) {
        Layout *layout = dynamic_cast <Layout*>(targed);
        if ( Qt::Vertical == layout->orientation()) {
            //qDebug() << "   * is vertical layout";
            if (down) {
                targed = dynamic_cast<AbstractElement *>(layout->itemAt(0));
            } else {
                targed = dynamic_cast<AbstractElement *>(layout->itemAt(layout->count()-1));
            }

        } else {
            //qDebug() << "   * is horizontal layout";
            child = dynamic_cast<AbstractElement *>(layout->itemAt(0));
            int len = skipChild( child, linePos);
            //qDebug() << "first child: "<< len <<"  "<< child->getType() <<"   "<< child->textE();
            while ( 0 < len) {
                //qDebug() << "skip child: "<<child->getType() <<"   "<< child->textE();
                linePos -= len;
                child = child->getNext();
                len = skipChild(child, linePos);
            }
            targed = child;
        }
    }


    int len = targed->textLength();
    qDebug() << "---- finito: " << targed->getType() <<"  "<< targed->textE();
    qDebug() << "---- finito: " << linePos << " " << len;

    linePos = linePos < len ? linePos : len;

    Item *ite = dynamic_cast <Item*>(targed);
    //qDebug() << "final:" << targed->getType() << "  " << ite->toPlainText();
    ite->setFocus();
    cursor = ite->textCursor();
    cursor.setPosition(linePos);
    ite->setTextCursor(cursor);
}


int CursorMoveCommand::skipChild(AbstractElement *child, int linePos) {
    if (child == NULL) {
        return 0;
    }
    // layout
    if (child->isLayoutE()) {
        Layout *layout = dynamic_cast <Layout*>(child);
        if ( Qt::Horizontal == layout->orientation()) {
            int len = child->textLength();
            if (len < linePos
                    && NULL != child->getNext()) {
                return len;
            }
        }
        return 0;

        // item
    } else {
        int len = child->textLength();
        if (len < linePos
                && NULL != child->getNext()) {
            return len;
        }
    }
    return 0;
}

void CursorMoveCommand::undo() {
    qDebug() << "UNDO cursorMoveCommand ";
}
