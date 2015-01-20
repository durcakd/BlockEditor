#include "mimedata.h"
#include "QDebug"
#include "scene/abstractelement.h"

MimeData::MimeData( AbstractElement *el)
    : QMimeData()
{

    _element = el;
}
