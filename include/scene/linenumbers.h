#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include <QDebug>
#include <QStaticText>
#include "blockscene.h"

class BlockScene;

class LineNumbers :
        public QObject,
        public QGraphicsItem
{
    Q_OBJECT

public:
    LineNumbers(BlockScene *scene);
    ~LineNumbers();
    QRectF boundingRect() const Q_DECL_OVERRIDE;

public slots:
    void updateLines(const QList<QRectF> &region);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/) Q_DECL_OVERRIDE;

private:
    BlockScene* _scene;
    std::vector<int> _lines;
};

#endif // LINENUMBERS_H
