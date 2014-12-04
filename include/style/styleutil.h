#ifndef STYLEMAP_H
#define STYLEMAP_H

#include <QString>
#include <QMap>
class Style;


class StyleUtil
{
public:
    StyleUtil();

    Style* getStyle(QString type) const;
    void addStyle(Style *style);

protected:

    QMap<QString, Style*> _styleMap;
};

#endif
