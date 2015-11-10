/****************************************************************************
** Meta object code from reading C++ file 'blockscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/scene/blockscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'blockscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BlockScene_t {
    QByteArrayData data[11];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BlockScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BlockScene_t qt_meta_stringdata_BlockScene = {
    {
QT_MOC_LITERAL(0, 0, 10), // "BlockScene"
QT_MOC_LITERAL(1, 11, 20), // "activeContextChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "Layout*"
QT_MOC_LITERAL(4, 41, 7), // "context"
QT_MOC_LITERAL(5, 49, 13), // "addParserItem"
QT_MOC_LITERAL(6, 63, 5), // "Item*"
QT_MOC_LITERAL(7, 69, 4), // "item"
QT_MOC_LITERAL(8, 74, 15), // "addParserLayout"
QT_MOC_LITERAL(9, 90, 6), // "layout"
QT_MOC_LITERAL(10, 97, 19) // "updateTreeNeighbors"

    },
    "BlockScene\0activeContextChanged\0\0"
    "Layout*\0context\0addParserItem\0Item*\0"
    "item\0addParserLayout\0layout\0"
    "updateTreeNeighbors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BlockScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x0a /* Public */,
       8,    1,   40,    2, 0x0a /* Public */,
      10,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    0x80000000 | 6, 0x80000000 | 6,    7,
    0x80000000 | 3, 0x80000000 | 3,    9,
    QMetaType::Void,

       0        // eod
};

void BlockScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BlockScene *_t = static_cast<BlockScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activeContextChanged((*reinterpret_cast< Layout*(*)>(_a[1]))); break;
        case 1: { Item* _r = _t->addParserItem((*reinterpret_cast< Item*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Item**>(_a[0]) = _r; }  break;
        case 2: { Layout* _r = _t->addParserLayout((*reinterpret_cast< Layout*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Layout**>(_a[0]) = _r; }  break;
        case 3: _t->updateTreeNeighbors(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Layout* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Layout* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BlockScene::*_t)(Layout * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BlockScene::activeContextChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject BlockScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_BlockScene.data,
      qt_meta_data_BlockScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BlockScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BlockScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BlockScene.stringdata0))
        return static_cast<void*>(const_cast< BlockScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int BlockScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BlockScene::activeContextChanged(Layout * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
