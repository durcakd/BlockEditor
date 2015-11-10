#ifndef BLANKITEM_H
#define BLANKITEM_H

#include <item/item.h>

class BlankItem :   public Item
{

public:
    explicit BlankItem(QString type, QString text, Style *style, QGraphicsLinearLayout *parent = 0);

public slots:

protected:

private:

};

#endif
