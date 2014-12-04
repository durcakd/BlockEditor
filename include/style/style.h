#ifndef STYLE_H
#define STYLE_H

#include <QString>

enum OrientationEnum {vertical, horizontal} ;

class Style
{

public:
    Style( const QString _styleType);

    QString getStyleType() const;
    OrientationEnum getOrientation() const;
    bool getIsItem() const;
    bool getIsLayout() const;

    void setOrientation(OrientationEnum orientation);
    void setOrientation(QString orientation);
    bool setIsItem(bool isItem);
    bool setIsLayout(bool isLayout);

protected:
    QString _styleType;
    OrientationEnum _orientation;
    bool _isItem;
    bool _isLayout;

};

#endif
