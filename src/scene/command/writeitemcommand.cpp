#include "scene/command/writeitemcommand.h"


#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>
#include <QGraphicsLayoutItem>
#include <QTextDocument>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "item/item.h"
#include "item/layout.h"
#include "item/abstractelement.h"
#include "style/styleutil.h"
#include "scene/blockscene.h"
#include "item/state/elementstate.h"
#include "item/state/elementstable.h"
#include "item/state/elementchanged.h"




WriteItemCommand::WriteItemCommand(QGraphicsItem *watched, int pos, int charsRemoved, int charsAdded)
    : Command()
{
    _item = static_cast<Item *>(watched) ;
    this->pos = pos;
    this->charsAdded = charsAdded;
    this->charsRemoved = charsRemoved;

}


void WriteItemCommand::execute() {

    qDebug() << "EXE writeItemCommand";
    qDebug() <<  pos <<"  "<< charsRemoved <<"  "<< charsAdded;

    //    QTextCursor cursor = _item->textCursor();
    //    if (_item->document()->isUndoAvailable()) {
    //        qDebug() << " orig       "<< _item->toPlainText();
    //        qDebug() << " orig-pos   "<<  cursor.position();
    //        _item->document()->undo( &cursor);
    //        qDebug() << " undo       "<< _item->toPlainText();
    //        qDebug() << " undo-pos   "<<  cursor.position();
    //    }

    // ADD
    if ( 0 == charsRemoved || charsAdded > charsRemoved) {
        charsAdded -= charsRemoved;
        charsRemoved = 0;
        qDebug() <<  pos <<"  "<< charsRemoved <<"  "<< charsAdded;

        if (1 == charsAdded ){
            simpleAddition();
        }

    }



}

void WriteItemCommand::simpleAddition() {
    qDebug() << "  simple addition";
    QTextCursor cursor(_item->textCursor());
    QChar newChar = _item->document()->characterAt(pos);
    Item *newItem = NULL;

    if ( _item->state()->isSpaced() == newChar.isSpace()) {
        qDebug() << "  spacedItem="<<_item->state()->isSpaced()<< "   simple soltion";
        _item->document()->clearUndoRedoStacks();


    } else {
        qDebug() << "  different item types, added:" << newChar;
        _item->document()->undo();
        Layout *parent = _item->getLayoutParrent();

        if (newChar.isSpace()) {
            // blank
            newItem = new Item( "changed_text", QString(newChar), StyleUtil::instance()->getStyle("changed_text"), _item->getLayoutParrent());
            newItem->setState(new ElementStable);
        } else {
            newItem = new Item( "changed_text", QString(newChar), StyleUtil::instance()->getStyle("changed_text"), _item->getLayoutParrent());
            newItem->setState(new ElementChanged);
        }

        if (0 == pos) {
            qDebug() << "add at start  new Item";
            Item *previous = dynamic_cast<Item*>(_item->nextPreviousAlsoHor(false));
            if (NULL != previous && previous->state()->isSpaced() == newChar.isSpace()) {
                qDebug() << "posible merge with previous";


//                QTextCursor cursor(previous->textCursor());
//                cursor.beginEditBlock();
//                cursor.movePosition(QTextCursor::StartOfWord);
//                cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
//                cursor.endEditBlock();


//                cursor.setPosition(previous->textLength(true));
//                cursor.insertText(QString(newChar));
                //previous->setTextCursor(cursor);
                //previous->setFocus();

            } else {


                parent->insertBefore(_item, newItem);
                BlockScene::instance()->addItem( newItem);
            }

        } else if (cursor.atEnd()) {
            qDebug() << "add at end  new item";
            Item *next = dynamic_cast<Item*>(_item->nextPreviousAlsoHor(true));
            if (NULL != next && next->state()->isSpaced() == newChar.isSpace()) {
                qDebug() << "posible merge with next";


                next->setFocus();
                next->blockSignals(true);
                QTextCursor c(next->textCursor());
                c.beginEditBlock();
                c.movePosition(QTextCursor::Start);
                c.insertText(QString(newChar));
                c.endEditBlock();
                next->setTextCursor(c);
                next->blockSignals(false);

            } else {
                parent->insertBehind(_item, newItem);
                BlockScene::instance()->addItem( newItem);
            }
        } else {
            qDebug() << "add in the middle";
        }

        //newItem->updateGeometry();
//        parent->invalidate();
//        parent->update();
//        parent->updateGeometry();
//        newItem->update();
//        newItem->updateGeometry();
//        _item->update();
//        _item->updateGeometry();



    }

    qDebug();



}


void WriteItemCommand::complexAddition() {

}


bool WriteItemCommand::hasSpace(const QString str) const {
    QString::ConstIterator it;
    for (it = str.constBegin(); it != str.constEnd(); it++) {
        if (it->isSpace()) {
            return true;
        }
    }
    return false;
}


void WriteItemCommand::undo() {
    qDebug() << "UNDO writeItemCommand ";
}

