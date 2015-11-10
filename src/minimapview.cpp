#include "include/minimapview.h"
#include "include/scene/blockscene.h"

MiniMapView::MiniMapView()
    : _contextOverlay(new QGraphicsScene())
{
    setAlignment(Qt::AlignTop|Qt::AlignLeft);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(false);
}

MiniMapView::~MiniMapView()
{
}

void MiniMapView::updateScene(const QList<QRectF> &rects)
{
    BlockScene* bs = dynamic_cast<BlockScene *>(scene());
    fitInView(bs->sceneRect(), Qt::KeepAspectRatio);
    setSceneRect(bs->_root->childrenBoundingRect().translated(20,0));
}

void MiniMapView::updateContext(const QRectF &rect)
{
    _contextOverlay->clear();
    _contextOverlay->addRect(0,mapFromScene(rect.topLeft()).y(),viewport()->width(),mapFromScene(rect).boundingRect().height(), Qt::NoPen, QBrush(QColor(0,0,0,50)));
}

void MiniMapView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    paintContextOverlay();
}

void MiniMapView::paintContextOverlay()
{
    if(_contextOverlay){
        QPainter p(viewport());
        p.setRenderHints(renderHints());
        QRectF r = _contextOverlay->itemsBoundingRect();
        _contextOverlay->render(&p, r.translated(0,mapFromScene(0,0).y()).adjusted(0,0,viewport()->width(),0), r);
        scene()->update();
    }
}
