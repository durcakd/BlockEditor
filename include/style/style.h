#ifndef STYLE_H
#define STYLE_H

#include <QString>
#include <QColor>

enum OrientationEnum {vertical, horizontal, any} ;

class Style
{

public:
    Style( const QString _styleType);

    QString getStyleType() const;
    OrientationEnum getOrientation() const;
    bool getIsItem() const;
    bool getIsLayout() const;
    bool getIsColor() const;
    bool getIsTransparent() const;
    bool getIsContext() const;
    QColor getBackground() const;

    void setOrientation(OrientationEnum orientation);
    void setOrientation(QString orientation);
    void setIsItem(bool isItem);
    void setIsLayout(bool isLayout);
    void setIsColor(bool isColor);
    void setIsTransparent(bool isTransparent);
    void setIsContext(bool isContext);
    void setBackground(QColor color);
    void setBackground(float r, float g, float b, float a);

    QString toString() const;

private:
    QString _styleType;
    OrientationEnum _orientation;
    bool _isItem;
    bool _isLayout;
    bool _isColor;
    bool _isTransparent;
    bool _isContext;
    QColor _background;

};

#endif
