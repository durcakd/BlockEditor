#ifndef BLOCKSCENE_H
#define BLOCKSCENE_H

#include <QGraphicsScene>

#include "item/item.h"
#include "item/layout.h"
#include "QStack"



class QGraphicsLinearLayout;
class QGraphicsWidget;
class SceneEventObserver;
class SceneState;
class Command;

class BlockScene : public QGraphicsScene
{
    Q_OBJECT

public:
    static BlockScene *instance( QObject *parent = 0);
    void addItem(QGraphicsItem *graphicItem);


    SceneState *getSceneState() const { return _sceneState;}
    void addCommand(Command *command);


public slots:

    Item* addParserItem( Item *item);
    Layout* addParserLayout( Layout *layout);
    void updateTreeNeighbors();

private:
    static BlockScene *inst;

    BlockScene( QObject *parent = 0);

    QGraphicsLinearLayout *_vLayout;
    QGraphicsWidget *_form;
    Layout *_root;
    SceneEventObserver *_eventFilter;
    SceneState *_sceneState;

    QStack<Command *> _commandStack;

};

#endif // MAINWINDOW_H
