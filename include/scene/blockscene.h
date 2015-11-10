#ifndef BLOCKSCENE_H
#define BLOCKSCENE_H

#include <QGraphicsScene>

#include "item/item.h"
#include "item/layout.h"
#include "scene/linenumbers.h"



class QGraphicsLinearLayout;
class QGraphicsWidget;
class LineNumbers;
class SceneEventObserver;
class SceneState;

class BlockScene : public QGraphicsScene
{
    Q_OBJECT

public:
    static BlockScene *instance( QObject *parent = 0);
    void addItem(QGraphicsItem *item);
    Layout *context(){ return _context; }
    void setContext(Layout *layout);
    void unsetContext();
    void test();

    AbstractElement *selectedLeaf() const {return _selectedLeaf;}
    AbstractElement *paintedElemement() const {return _paintedElemement;}
    SceneState *getSceneState() const { return _sceneState;}
    Layout *_root;
    //LineNumbers *lineNumbers() const { return _linenumbers; };

    void setSelectedE(AbstractElement *selectedLeaf, AbstractElement *paintedElemement)
    {
        _selectedLeaf = selectedLeaf;
        _paintedElemement = paintedElemement;
    }

public slots:
    Item* addParserItem( Item *item);
    Layout* addParserLayout( Layout *layout);
    void updateTreeNeighbors();

signals:
    void activeContextChanged(Layout *context);

private:
    static BlockScene *inst;

    BlockScene( QObject *parent = 0);

    //QGraphicsLinearLayout *_vLayout;
    QGraphicsWidget *_form;
    AbstractElement *_selectedLeaf;
    AbstractElement *_paintedElemement;
    Layout *_context;
    SceneEventObserver *_eventFilter;
    SceneState *_sceneState;

};

#endif // MAINWINDOW_H
