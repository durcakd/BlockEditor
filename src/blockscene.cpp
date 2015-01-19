#include "blockscene.h"
#include "QDebug"

#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QLabel>

#include "style/style.h"
#include "parser.h"

#include "scene/rectitemlayout.h"


BlockScene::BlockScene( QObject *parent)
    : QGraphicsScene(parent)
{
    //setSceneRect(0, 0, 800, 600);
    _form = new QGraphicsWidget;
    addItem(_form);

    //test();

}

void BlockScene::addItem(QGraphicsItem *item) {
    qDebug() << "A  ";
    QGraphicsScene::addItem(item);
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

QConnect:connect( item->_document, SIGNAL(contentsChanged()), _root, SLOT(childItemChanged()));

    return item;
}

Layout* BlockScene::addParserLayout( Layout *layout) {
    qDebug() << "-- added layout " << layout->getType();
    if( layout->parentLayoutItem() == NULL){

        qDebug() << "also in scene";
        _form->setLayout(layout);
        _root = layout;
        _root->setParrentE(NULL);
        setSceneRect(0, 0, 800, 600);

    } else {
        qDebug() << "      with parrent: " << layout->getLayoutParrent()->getType();
        //Layout *parrent = dynamic_cast<Layout*>( layout->getLayoutParrent());
        //parrent->addLayoutChild(layout);
        layout->getLayoutParrent()->addItem(layout);
    }

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


void BlockScene::test()
{
    Parser *parser = new Parser("lua");
    Style *st = parser->_styleUtil.getStyle("block");

    Item *i1 =  new Item("item", "1", st);
    Item *i2 =  new Item("item", "2", st);
    Item *i3 =  new Item("item", "3", st);
    Item *i4 =  new Item("item", "4", st);
    Item *i5 =  new Item("item", "5", st);
    Item *i6 =  new Item("item", "6", st);
    Item *i7 =  new Item("item", "7", st);
    Item *i8 =  new Item("item", "8", st);
    Item *i9 =  new Item("item", "9", st);
    Item *i10 =  new Item("item", "10", st);


    QGraphicsLinearLayout *v1 = new QGraphicsLinearLayout(Qt::Vertical);
    //    QGraphicsLinearLayout *vv1 = new QGraphicsLinearLayout(Qt::Vertical, v1);
    //QGraphicsLinearLayout *hh2 = new QGraphicsLinearLayout(v1);
    QGraphicsLinearLayout *hh2 = new Layout("cycle", st, dynamic_cast<QGraphicsLayoutItem*>(v1));
    //    QGraphicsLinearLayout *vv3 = new QGraphicsLinearLayout(Qt::Vertical, v1);
    //    QGraphicsLinearLayout *vv4 = new QGraphicsLinearLayout(Qt::Vertical, vv1);
    //    QGraphicsLinearLayout *vv5 = new QGraphicsLinearLayout(Qt::Vertical, vv1);
    //    QGraphicsLinearLayout *vv6 = new QGraphicsLinearLayout(Qt::Vertical, vv4);


    v1->addItem(i1);
    v1->addItem(i2);
    v1->addItem(i3);
    //   v1->addItem(vv1);
    //  vv1->addItem(vv4);
    //  vv1->addItem(vv5);
    //  vv4->addItem(vv6);
    //  v1->addItem(hh2);
    //  v1->addItem(vv3);


    //    v1->addItem(i2);
    //    vv1->addItem(i3);
    //    vv4->addItem(i4);
    //    vv5->addItem(i5);
    //    vv6->addItem(i6);
    //    v1->addItem(i7);
    //    hh2->addItem(i8);
    //    hh2->addItem(i9);
    //    vv3->addItem(i10);
    _form->setLayout(v1);

    addItem(i1);
    addItem(i2);
    addItem(i3);
        addItem(i4);
        addItem(i5);
    //    addItem(i6);
    //    addItem(i7);
    //    addItem(i8);
    //    addItem(i9);
    //    addItem(i10);


    RectLayout *r1 = new RectLayout(0,0,10,10);
    RectLayout *r2 = new RectLayout(0,0,15,15);
    RectLayout *r3 = new RectLayout(0,0,20,20);
    RectLayout *r0 = new RectLayout(0,0,40,40);
    addItem(r1);
    addItem(r2);
    addItem(r3);
    addItem(r0);

    //r2->setVisible(false);



    //v1->addItem(dynamic_cast<QGraphicsLayoutItem*>(r0));
    v1->addItem(i4);
 //   r0->addItem(dynamic_cast<QGraphicsLinearLayout*>(r1));
 //   r0->addItem(dynamic_cast<QGraphicsLinearLayout*>(r2));
 //   r0->addItem(dynamic_cast<QGraphicsLinearLayout*>(r3));

  //  addItem(dynamic_cast<QGraphicsItem*>(hh2));
    v1->addItem(i3);
   v1->addItem(hh2);
/*
        hh2->addItem(r1);
        hh2->addItem(r2);
        hh2->addItem(r3);
//    r0->activate();
//    r0->update();
//    r0->updateGeometry();

    qDebug() << "v1 islayout   " << v1->isLayout();
    qDebug() << "r0 islayout   " << r0->isLayout();
    qDebug() << "v1 isActive()   " << v1->isActivated();
    qDebug() << "r0 isActive   " << r0->isActivated();
*/
}
