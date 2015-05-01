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
        verCursorMovement2(cursor, false);
        break;
    case Qt::Key_Down:
        verCursorMovement2(cursor, true);
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

void CursorMoveCommand::verCursorMovement2(QTextCursor &cursor, bool down) {
    int linePos = cursor.position();

    Layout *parent = _item->getLayoutParrent();
    const AbstractElement *element = _item;

    qDebug() << "111111111111111";

    // calculate position on line
    while (parent != NULL && Qt::Horizontal == parent->orientation()) {
        AbstractElement *neighbor = element->getPrevius();
        while (neighbor) {
            linePos += neighbor->textLength();
            neighbor = neighbor->getPrevius();
        }
        element = parent;
        parent = parent->getLayoutParrent();
    }

    if (parent == NULL) {
        qDebug() << "WARNING!!! vertical cursor movement 1, parent=NULL";
        return;
    }



    qDebug() << "2222222222222222   linePos= "  << linePos;
    // find vertical , that has neighbors
    while (NULL != parent && NULL == element->nextPrevius(down)) {  // there can be more vertical
        qDebug() << "  - vertical nahovno parent: "<< parent->getType()  << "  " << parent->textE();
        element = parent;
        parent = parent->getLayoutParrent();
    }
    if (parent == NULL) {
        qDebug() << "WARNING!!! vertical cursor movement 2, parent=NULL";
        return;
    }




    AbstractElement *targed = element->nextPrevius(down);
    AbstractElement *child = NULL;
    qDebug() << "  - stary line: "<< element->getType()  << "  " << element->textE();
    qDebug() << "\n\n33333333333333333   linePos= "  << linePos;



    // right

    qDebug() << "----- novy targed: "<< targed->getType()  << "  " << targed->textE();

    while (targed->isLayoutE()) {
        Layout *layout = dynamic_cast <Layout*>(targed);
        if ( Qt::Vertical == layout->orientation()) {
            qDebug() << "   * is vertical layout";
            if (down) {
                targed = dynamic_cast<AbstractElement *>(layout->itemAt(0));
            } else {
                targed = dynamic_cast<AbstractElement *>(layout->itemAt(layout->count()-1));
            }

        } else {
            qDebug() << "   * is horizontal layout";
            child = dynamic_cast<AbstractElement *>(layout->itemAt(0));
            int len = skipChild( child, linePos);
            qDebug() << "first child: "<< len <<"  "<< child->getType() <<"   "<< child->textE();
            while ( 0 < len) {
                qDebug() << "skip child: "<<child->getType() <<"   "<< child->textE();
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
     } else {
         int len = child->textLength();
         if (len < linePos
                 && NULL != child->getNext()) {
           return len;
         }
     }
     return 0;
 }


void CursorMoveCommand::verCursorMovement(QTextCursor &cursor, bool down) {
    AbstractElement *targed = static_cast<AbstractElement *>(_item) ;;
    int linePos = cursor.position();
    // qDebug() << "";
    //qDebug() << "start " << linePos << "  " << getType() << "  " << toPlainText();
    // left
    while( NULL != targed) {
        AbstractElement *parrent = targed->getLayoutParrent();
        if( NULL != parrent && OrientationEnum::vertical == parrent->styleE()->getOrientation()) {
            break;
        }
        while ( NULL != targed->nextPrevius(false)) {
            targed = targed->nextPrevius(false);
            linePos += targed->textLength();
            //qDebug() << " + "<< targed->textLength() << " = " << linePos << "    " << targed->getType();
        }

        //qDebug() << "up parrent "<< targed->getType() << "  " << targed->textE();
        targed = parrent;

    }
    // down/up


    if (NULL!= targed) {qDebug() << "1. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();}
    while (NULL != targed && NULL == targed->nextPrevius(down)) {  // there can be more vertical
        targed = targed->getLayoutParrent();
        //if (NULL!= targed) {qDebug() << "2. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();}
    }
    if (NULL == targed) { return; }
    targed = targed->nextPrevius(down);


    //qDebug() << "3. up/down"   << linePos << "    " << targed << "  " << targed->getType() << "  " << targed->textE();
    // right
    int tlen;
    while (targed->isLayoutE()) {
        //qDebug() << "down child    " << targed->getType();
        bool isHorizontal = OrientationEnum::horizontal == targed->styleE()->getOrientation();

        Layout *lay = dynamic_cast <Layout*>(targed);
        targed = dynamic_cast<AbstractElement*>(lay->itemAt(0)); // TODO no children?

        tlen = targed->textLength();
        while (isHorizontal
               && tlen < linePos
               && NULL != targed->nextPrevius(true)) {
            qDebug() << " - "<< tlen << " = " << linePos << "    " << targed->getType();
            targed = targed->nextPrevius(true);
            linePos -= (tlen);
            tlen = targed->textLength();
        }
    }


    Item *ite = dynamic_cast <Item*>(targed);
    qDebug() << "final:" << targed->getType() << "  " << ite->toPlainText();
    ite->setFocus();
    cursor = ite->textCursor();
    tlen = targed->textLength();
    linePos = linePos < tlen ? linePos : tlen;
    cursor.setPosition(linePos);
    ite->setTextCursor(cursor);
}

void CursorMoveCommand::undo() {
    qDebug() << "UNDO cursorMoveCommand ";
}
