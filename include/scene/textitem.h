#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "scene/item.h"

class TextItem :   public Item
{

public:
    explicit TextItem(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);


public slots:


protected:

private:

};


#endif
