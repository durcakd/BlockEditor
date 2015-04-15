#include "scene/command/cursormovecommand.h"


#include <QDebug>


CursorMoveCommand::CursorMoveCommand()
    : Command()
{

}


void CursorMoveCommand::execute() {
    qDebug() << "EXE cursorMoveCommand";
}
