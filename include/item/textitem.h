#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "item/item.h"

class TextItem :   public Item
{

public:
    explicit TextItem(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);

    bool isSpaceItem() const;

public slots:


protected:

private:

};


#endif
