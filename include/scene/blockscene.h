#ifndef BLOCKSCENE_H
#define BLOCKSCENE_H

#include <QGraphicsScene>

#include "item/item.h"
#include "item/layout.h"
#include "sceneeventobserver.h"

class QGraphicsLinearLayout;
class QGraphicsWidget;

class BlockScene : public QGraphicsScene
{
    Q_OBJECT

public:
    static BlockScene *instance( QObject *parent = 0);
    void addItem(QGraphicsItem *item);
    void test();

    AbstractElement *selectedLeaf() const {return _selectedLeaf;}
    AbstractElement *paintedElemement() const {return _paintedElemement;}

    void setSelectedE(AbstractElement *selectedLeaf, AbstractElement *paintedElemement)
    {
        _selectedLeaf = selectedLeaf;
        _paintedElemement = paintedElemement;
    }

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
    AbstractElement *_selectedLeaf;
    AbstractElement *_paintedElemement;
    SceneEventObserver *_eventFilter;

};

#endif // MAINWINDOW_H