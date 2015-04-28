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
#include "scene/parser.h"



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
        //_item->document()->clearUndoRedoStacks();


    } else {
        qDebug() << "  different item types, added:" << newChar;
        qDebug() << _item->document()->isUndoAvailable();
        _item->blockSignals(true);
        // undo
        if (0 == pos) {
            _item->setPlainText(_item->toPlainText().mid(1));
        } else {
            //_item->document()->undo(&cursor);
            cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
            _item->setTextCursor(cursor);
        }
        _item->blockSignals(false);


        Layout *parent = _item->getLayoutParrent();


        if (newChar.isSpace()) {
            newItem = Parser::instance()->createStableItem(_item->getLayoutParrent(), QString(newChar));
        } else {
            newItem = Parser::instance()->createChangedItem(_item->getLayoutParrent(), QString(newChar));
        }


        if (0 == pos) {
            qDebug() << "add at start  new Item";
            Item *previous = dynamic_cast<Item*>(_item->nextPreviousAlsoHor(false));
            if (NULL != previous && previous->state()->isSpaced() == newChar.isSpace()) {
                qDebug() << "posible merge with previous";

                _item->clearFocus();
                _item->show();
                previous->setFocus();
                previous->blockSignals(true);
                cursor = previous->textCursor();
                cursor.beginEditBlock();
                cursor.movePosition(QTextCursor::End);
                cursor.insertText(QString(newChar));
                cursor.endEditBlock();
                previous->setTextCursor(cursor);
                previous->blockSignals(false);

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
                cursor = next->textCursor();
                cursor.beginEditBlock();
                cursor.movePosition(QTextCursor::Start);
                cursor.insertText(QString(newChar));
                cursor.endEditBlock();
                next->setTextCursor(cursor);
                next->blockSignals(false);


            } else {
                parent->insertBehind(_item, newItem);
                BlockScene::instance()->addItem( newItem);
            }
        } else {
            qDebug() << "add in the middle";
        }


        //newItem->updateGeometry();
        parent->invalidate();
        parent->update();
        parent->updateGeometry();
//        newItem->update();
//        newItem->updateGeometry();
        _item->update();
        _item->updateGeometry();


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

