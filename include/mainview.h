#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>

class MainView : public QGraphicsView
{
    Q_OBJECT

public:
    MainView();
    ~MainView();
    void setScene(QGraphicsScene *scene);

public slots:
    void overlayChanged(){ update(); }
    void updateScene(const QList<QRectF> & rects);
    void contextChanged();
    void viewScrolled();

signals:
    void scopeChanged(QRectF rect);

private:
    QGraphicsScene* _lineNumbersOverlay;
    QGraphicsScene* _contextOverlay;
    void paintEvent(QPaintEvent *event);
    void paintLineNumbersOverlay();
    void paintContextOverlay();
};

#endif // MAINVIEW_H
