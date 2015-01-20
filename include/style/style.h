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
    bool getIsColor() const;

    void setOrientation(OrientationEnum orientation);
    void setOrientation(QString orientation);
    bool setIsItem(bool isItem);
    bool setIsLayout(bool isLayout);
    bool setIsColor(bool isColor);

protected:
    QString _styleType;
    OrientationEnum _orientation;
    bool _isItem;
    bool _isLayout;
    bool _isColor;

};

#endif
