#include "style/style.h"
#include <QDebug>

Style::Style( const QString styleType)
{
    _styleType = styleType;
}

QString Style::getStyleType() const {
    return _styleType;
}

OrientationEnum Style::getOrientation() const {
    return _orientation;
}

bool Style::getIsItem() const {
    return _isItem;
}

bool Style::getIsLayout() const {
    return _isLayout;
}

void Style::setOrientation(OrientationEnum orientation) {
    _orientation = orientation;
}
void Style::setOrientation(QString orientation) {
    if (0 == orientation.compare("horizontal")) {
        setOrientation(OrientationEnum::horizontal);
    }
    else if (0 == orientation.compare("vertical")) {
        setOrientation(OrientationEnum::vertical);
    }
}

bool Style::setIsItem(bool isItem) {
    _isItem = isItem;
}

bool Style::setIsLayout(bool isLayout) {
    _isLayout = isLayout;
}
