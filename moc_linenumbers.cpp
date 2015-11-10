/****************************************************************************
** Meta object code from reading C++ file 'linenumbers.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/scene/linenumbers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linenumbers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LineNumbers_t {
    QByteArrayData data[12];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LineNumbers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LineNumbers_t qt_meta_stringdata_LineNumbers = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LineNumbers"
QT_MOC_LITERAL(1, 12, 11), // "updateLines"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "QList<QRectF>"
QT_MOC_LITERAL(4, 39, 6), // "region"
QT_MOC_LITERAL(5, 46, 5), // "paint"
QT_MOC_LITERAL(6, 52, 9), // "QPainter*"
QT_MOC_LITERAL(7, 62, 7), // "painter"
QT_MOC_LITERAL(8, 70, 31), // "const QStyleOptionGraphicsItem*"
QT_MOC_LITERAL(9, 102, 6), // "option"
QT_MOC_LITERAL(10, 109, 8), // "QWidget*"
QT_MOC_LITERAL(11, 118, 6) // "widget"

    },
    "LineNumbers\0updateLines\0\0QList<QRectF>\0"
    "region\0paint\0QPainter*\0painter\0"
    "const QStyleOptionGraphicsItem*\0option\0"
    "QWidget*\0widget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LineNumbers[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       5,    3,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 10,    7,    9,   11,

       0        // eod
};

void LineNumbers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LineNumbers *_t = static_cast<LineNumbers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLines((*reinterpret_cast< const QList<QRectF>(*)>(_a[1]))); break;
        case 1: _t->paint((*reinterpret_cast< QPainter*(*)>(_a[1])),(*reinterpret_cast< const QStyleOptionGraphicsItem*(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QRectF> >(); break;
            }
            break;
        }
    }
}

const QMetaObject LineNumbers::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LineNumbers.data,
      qt_meta_data_LineNumbers,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LineNumbers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LineNumbers::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LineNumbers.stringdata0))
        return static_cast<void*>(const_cast< LineNumbers*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< LineNumbers*>(this));
    return QObject::qt_metacast(_clname);
}

int LineNumbers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
