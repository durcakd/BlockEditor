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
        qDebug() << "*"<<  pos <<"  "<< charsRemoved <<"  "<< charsAdded;

        if (1 == charsAdded ){
            simpleAddition();
        }
    }

    // REMOVE
    else if (1 == charsRemoved) {
        simpleRemove();
    }
}

void WriteItemCommand::simpleRemove() {
    qDebug() << "  simple remove";
    if (_item->textLength() == 0) {
        qDebug() << "remove item";
        AbstractElement *toRemove = _item;
        Layout *parent = _item->getLayoutParrent();

        while (parent != NULL && parent->count() < 2) {
            qDebug() << "up";
            toRemove = parent;
            parent = parent->getLayoutParrent();
        }

        if (parent != NULL) {
            // select else one
            Item *instead = dynamic_cast <Item*>(findInsteadtoSelect());
            instead->setFocus();

            // remove
            parent->removeElement(toRemove);
            BlockScene::instance()->removeItem( dynamic_cast<QGraphicsItem *>(toRemove));

            parent->edited(instead);
        } else {
            _item->edited(_item);
        }
    } else {
        _item->edited(_item);
    }
}

void WriteItemCommand::simpleAdditionEnter() {
    qDebug() << "ENTER";
    undoSimpleAddition();

    QString leftLine = _item->textOnLineForPos(pos, false);
    QString rightLine = _item->textOnLineForPos(pos, true);
    qDebug() << "left:  "<< leftLine;
    qDebug() << "right: "<< rightLine;


    Layout *vParent = _item->getLayoutParrent();
    AbstractElement *toReplace = _item;
    while (vParent != NULL && Qt::Horizontal == vParent->orientation()) {
        toReplace = vParent;
        vParent = vParent->getLayoutParrent();
    }
    if (vParent == NULL) {
        qDebug() << "WARNING!!! simple addition enter - vertical parent is NULL";
        return;
    }

    bool addLeft = true;
    bool addRight = true;
    if (rightLine.isEmpty()) {
        rightLine = " ";
        addLeft = false;
    }
    if (leftLine.isEmpty()) {
        leftLine = " ";
        addRight = false;
    }

    Item *rightItem = NULL;
    Item *leftItem = NULL;
    if (addRight) {
        qDebug() << "   addd right half";
        rightItem = createItemForInsert( !addLeft, rightLine, vParent);

        vParent->insertBehind(toReplace, rightItem);
        BlockScene::instance()->addItem(rightItem);

        rightItem->setFocus();
        QTextCursor cursor(rightItem->textCursor());
        cursor.setPosition(0);
        rightItem->setTextCursor(cursor);
    }
    if (addLeft) {
        qDebug() << "   addd left half";
        leftItem = createItemForInsert( !addRight, leftLine, vParent);

        vParent->insertBefore(toReplace, leftItem);
        BlockScene::instance()->addItem(leftItem);
    }
    if (addLeft && addRight) {
        qDebug() << "  remove old line";
        vParent->removeElement(toReplace);
        BlockScene::instance()->removeItem( dynamic_cast<QGraphicsItem *>(toReplace));

        leftItem->edited(rightItem);
        rightItem->edited(rightItem);
    }
}

void WriteItemCommand::simpleAddition() {

    qDebug() << "  simple addition";
    QTextCursor cursor(_item->textCursor());
    QChar newChar = _item->document()->characterAt(pos);

    if (newChar.unicode() == 8233) {
        simpleAdditionEnter();
        return; // TODO
    }

    if ( _item->state()->isSpaced() == newChar.isSpace()) {
        _item->edited(_item);

    } else {
        qDebug() << "  different item types, added:" << newChar;
        if (0 == pos) {
            simpleAdditionStartEnd(newChar, true);
        } else if (cursor.atEnd()) {
            simpleAdditionStartEnd(newChar, false);
        } else {
            simpleAdditionMiddle(newChar);
        }
    }
}

void WriteItemCommand::simpleAdditionMiddle(QChar newChar) {
    qDebug() << " add in the middle";
    Layout *parent = _item->getLayoutParrent();

    QString text = _item->toPlainText();
    _item->blockSignals(true);
    _item->setPlainText(text.mid(0,pos));
    _item->blockSignals(false);

    Item *second = createItemForInsert( newChar);
    Item *third = createItemForInsert( !newChar.isSpace(), text.mid(pos+1));

    parent->insertBehind(_item, second);
    parent->insertBehind(second, third);
    BlockScene::instance()->addItem(second);
    BlockScene::instance()->addItem(third);

    second->setFocus();
    QTextCursor cursor = second->textCursor();
    cursor.movePosition(QTextCursor::End);
    second->setTextCursor(cursor);

    _item->edited(second);
    second->edited(second);
    third->edited(second);
}


void WriteItemCommand::simpleAdditionStartEnd(QChar newChar, bool inStart) {
    qDebug() << ( inStart ? "add at start  new Item" : "add at end  new item");
    undoSimpleAddition();
    Layout *parent = _item->getLayoutParrent();
    Item *neighbor = dynamic_cast<Item*>(_item->nextPreviousAlsoHor( !inStart));

    if (NULL != neighbor && neighbor->state()->isSpaced() == newChar.isSpace()) {
        qDebug() << ( inStart ? "merge with previous" : "merge with next");

        neighbor->setFocus();
        neighbor->blockSignals(true);
        QTextCursor cursor = neighbor->textCursor();
        cursor.beginEditBlock();
        if (inStart) {
            cursor.movePosition(QTextCursor::End);
        } else {
            cursor.movePosition(QTextCursor::Start);
        }
        cursor.insertText(QString(newChar));
        cursor.endEditBlock();
        neighbor->setTextCursor(cursor);
        neighbor->blockSignals(false);

        neighbor->edited(neighbor);
    } else {
        qDebug() << "no merge";
        Item *newItem = createItemForInsert( newChar);
        if (inStart) {
            parent->insertBefore(_item, newItem);
        } else {
            parent->insertBehind(_item, newItem);
        }
        BlockScene::instance()->addItem(newItem);
        newItem->edited(newItem);
    }
}


Item *WriteItemCommand::createItemForInsert(QChar newChar) {
    return createItemForInsert(newChar.isSpace(), QString(newChar));
}

Item *WriteItemCommand::createItemForInsert(bool stable, QString text) {
    return createItemForInsert(stable, text, _item->getLayoutParrent());
}

Item *WriteItemCommand::createItemForInsert(bool stable, QString text, Layout *parent) {
    if (stable) {
        return Parser::instance()->createStableItem(parent, text);
    } else {
        //return Parser::instance()->createChangedItem(_item->getLayoutParrent(), text);
        return Parser::instance()->createNewItem(parent, "changed_text", text);
    }
}

void WriteItemCommand::undoSimpleAddition() {
    _item->blockSignals(true);
    // undo
    if (0 == pos) {
        _item->setPlainText(_item->toPlainText().mid(1));
    } else {
        //_item->document()->undo(&cursor);
        QTextCursor cursor(_item->textCursor());
        cursor.clearSelection();
        cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        _item->setTextCursor(cursor);
    }
    _item->blockSignals(false);
}

AbstractElement *WriteItemCommand::findInsteadtoSelect() {
    AbstractElement *instead = _item->nextPreviousAlsoHor(false);
    if (NULL == instead) {
        instead = _item->nextPreviousAlsoHor(true);
    }
    if (NULL == instead) {
        instead = _item->nextPreviousAlsoVert(false);
    }
    if (NULL == instead) {
        instead = _item->nextPreviousAlsoVert(true);
    }
    return instead;
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



void WriteItemCommand::complexAddition() {

}

void WriteItemCommand::undo() {
    qDebug() << "UNDO writeItemCommand ";
}

