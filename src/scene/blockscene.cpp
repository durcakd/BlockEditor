#include "scene/blockscene.h"
#include "QDebug"

#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QGraphicsWidget>
#include <QLabel>

#include "scene/reparser.h"
#include "scene/sceneeventobserver.h"
#include "scene/scenestate.h"
#include "scene/command/command.h"

BlockScene *BlockScene::inst = 0;

BlockScene *BlockScene::instance( QObject *parent)
{
    if (!inst) {
        inst = new BlockScene(parent);
    }
    return inst;
}


BlockScene::BlockScene( QObject *parent)
    : QGraphicsScene(parent)
{
    //setSceneRect(0, 0, 300, 300);
    _form = new QGraphicsWidget;
    addItem(_form);

    _sceneState = new SceneState;
    _reparser = new Reparser();
    _eventFilter = new SceneEventObserver;
    addItem(_eventFilter);

}

void BlockScene::addItem(QGraphicsItem *graphicItem, bool recursive) {
    //qDebug() << "A  ";
    QGraphicsScene::addItem(graphicItem);

    Item   *item = dynamic_cast<Item *>( graphicItem);
    Layout *layout = dynamic_cast<Layout *>( graphicItem);
    if (item) {
        item->attach(_reparser);
        graphicItem->installSceneEventFilter( _eventFilter);
QConnect:connect( item->document(), SIGNAL(contentsChanged()), _root, SLOT(childItemChanged()));
    }

    if (layout) {
        layout->attach(_reparser);
    }

    if (recursive && layout) {
        for (int i=0; i < layout->count(); i++) {
            QGraphicsItem *child = dynamic_cast<QGraphicsItem*>(layout->itemAt(i));
            if (child) {
                addItem(child, recursive);
            }
        }
    }
}

void BlockScene::removeItem(QGraphicsItem *graphicItem, bool recursive) {

    graphicItem->removeSceneEventFilter(_eventFilter);
    AbstractElement *element = dynamic_cast<AbstractElement *>( graphicItem);
    if (element) {
        element->detach(_reparser);

    }


    if (recursive) {
        Layout *layout = dynamic_cast<Layout*>( graphicItem);
        if (layout) {
            for (int i=0; i < layout->count(); i++) {
                QGraphicsItem *child = dynamic_cast<QGraphicsItem*>(layout->itemAt(i));
                if (child) {
                    removeItem(child, recursive);
                }
            }
        }
    }
    QGraphicsScene::removeItem(graphicItem);
}

Item *BlockScene::addParserItem(Item *item)
{
    //qDebug() << "-- added item " << item->toPlainText() << "   " << item->getType();

    if( item->getLayoutParrent() == NULL){
        //addItem(item);
      //  qDebug() << "also in scene";

    } else {
        //qDebug() << "      with parrent: " << item->getLayoutParrent()->getType();

        item->getLayoutParrent()->addItem(item);
        //item->getLayoutParrent()->activate();
        //item->getLayoutParrent()->updateGeometry();
        //qDebug() << "islayout" << item->getLayoutParrent()->isLayout();

        //Layout *parrent = dynamic_cast<Layout*>( item->getLayoutParrent());
        //parrent->addLayoutChild(item);

    }
    addItem( item);
    return item;
}

Layout* BlockScene::addParserLayout( Layout *layout) {
    //qDebug() << "-- added layout " << layout->getType();
    if( layout->parentLayoutItem() == NULL){
       // qDebug() << "also in scene";
        _form->setLayout(layout);
        _root = layout;
        _root->setLayoutParrent(NULL);

        //setSceneRect(0, 0, 800, 600);

    } else {
      //  qDebug() << "      with parrent: " << layout->getLayoutParrent()->getType();
        //Layout *parrent = dynamic_cast<Layout*>( layout->getLayoutParrent());
        //parrent->addLayoutChild(layout);
        layout->getLayoutParrent()->addItem(layout);

    }
    addItem( layout);
    return layout;
}

void BlockScene::updateTreeNeighbors()
{
    if (NULL == _root) {
        qDebug() << "Warning: BlockScene::updateTreeNeighbors(): _root is null.";
        return;
    }
    _root->updateChildNeighbors();

}

void BlockScene::addCommand(Command *command)
{
    command->execute();
    _commandStack.push( command);
}

