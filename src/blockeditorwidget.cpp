#include "blockeditorwidget.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QDebug>
#include <QTime>

#include "scene/blockscene.h"
#include "scene/parser.h"


BlockEditorWidget::BlockEditorWidget()
{
    view = new QGraphicsView();
    view->showMaximized();
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene = BlockScene::instance(view);
    view->setScene(scene);

    _textType = "lua";
    parser = Parser::instance(_textType);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
    setMinimumSize(400,300);
}

void BlockEditorWidget::editText(const QString text) {
    _text = text;
    qDebug() << "--- start parsing time measure -------";
    QTime time;
    time.start();
    scene->addNewRoot(parser->parse(_text));
    double runTime = time.elapsed();// / 1000.0;
    qDebug() << "--- parsing time= "<< QString::number(runTime, 'f', 2);
}

void BlockEditorWidget::clearPreviousEditedText() {

}

QString BlockEditorWidget::getEditedText() {

}


