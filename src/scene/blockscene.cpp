#include "scene/blockscene.h"
#include "QDebug"

#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QGraphicsWidget>
#include <QLabel>

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
    _eventFilter = new SceneEventObserver;
    addItem(_eventFilter);

}

void BlockScene::addItem(QGraphicsItem *graphicItem) {
    qDebug() << "A  ";
    QGraphicsScene::addItem(graphicItem);
    Item *item = dynamic_cast<Item *>( graphicItem);
    if (item) {
        graphicItem->installSceneEventFilter( _eventFilter);
        QConnect:connect( item->_document, SIGNAL(contentsChanged()), _root, SLOT(childItemChanged()));
    }
}

Item *BlockScene::addParserItem(Item *item)
{
    qDebug() << "-- added item " << item->toPlainText() << "   " << item->getType();

    if( item->getLayoutParrent() == NULL){
        //addItem(item);
        qDebug() << "also in scene";

    } else {
        qDebug() << "      with parrent: " << item->getLayoutParrent()->getType();

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
    qDebug() << "-- added layout " << layout->getType();
    if( layout->parentLayoutItem() == NULL){
        qDebug() << "also in scene";
        _form->setLayout(layout);
        _root = layout;
        _root->setLayoutParrent(NULL);

        //setSceneRect(0, 0, 800, 600);

    } else {
        qDebug() << "      with parrent: " << layout->getLayoutParrent()->getType();
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

