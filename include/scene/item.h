#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsLayoutItem>
#include <QSizeF>
#include <QObject>

#include "scene/abstractelement.h"

//class QGraphicsSceneDragDropEvent;
//class QGraphicsSceneMouseEvent;



class Item :   public QGraphicsLayoutItem, public QGraphicsTextItem, public AbstractElement
{

public:
    explicit Item(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);

    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    QSizeF elementSizeHint(Qt::SizeHint which) const;

    QTextDocument *_document;
    bool isLayoutE() const;

    QString getText() const {return _text;}

    void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/);

public slots:
    void textUpdatedSlot();

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent ( QKeyEvent * event );

protected:
    void horCursorMovement(QTextCursor &cursor, bool toNext);
    void verCursorMovement(QTextCursor &cursor, bool down);
    int textLength(bool length = true) const;
    QString textE() const;


    // when draged on area
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) ;//Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) ;// Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;


    QString _text;
    bool dragOver;
    QColor color;

private:

};


#endif
