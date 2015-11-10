#ifndef MINIMAPVIEW_H
#define MINIMAPVIEW_H

#include <QGraphicsView>

class BlockScene;

class MiniMapView : public QGraphicsView
{
    Q_OBJECT

public:
    MiniMapView();
    ~MiniMapView();

public slots:
    void updateScene(const QList<QRectF> & rects);
    void updateContext(const QRectF &rect);

private:
    QGraphicsScene* _contextOverlay;
    void paintEvent(QPaintEvent *event);
    void paintContextOverlay();

};

#endif // MINIMAPVIEW_H
