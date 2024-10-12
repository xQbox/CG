/****************************************************************************
** Meta object code from reading C++ file 'mymainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mymainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyMainWindow_t {
    QByteArrayData data[17];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyMainWindow_t qt_meta_stringdata_MyMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyMainWindow"
QT_MOC_LITERAL(1, 13, 10), // "moveObject"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "rotateClockwise"
QT_MOC_LITERAL(4, 41, 22), // "rotateCounterClockwise"
QT_MOC_LITERAL(5, 64, 14), // "resetToDefault"
QT_MOC_LITERAL(6, 79, 10), // "uploadSave"
QT_MOC_LITERAL(7, 90, 10), // "toggleGrid"
QT_MOC_LITERAL(8, 101, 7), // "checked"
QT_MOC_LITERAL(9, 109, 10), // "toggleAxis"
QT_MOC_LITERAL(10, 120, 12), // "toggleOrigin"
QT_MOC_LITERAL(11, 133, 13), // "toggleEmulate"
QT_MOC_LITERAL(12, 147, 8), // "showHelp"
QT_MOC_LITERAL(13, 156, 15), // "showImplementer"
QT_MOC_LITERAL(14, 172, 10), // "closeEvent"
QT_MOC_LITERAL(15, 183, 12), // "QCloseEvent*"
QT_MOC_LITERAL(16, 196, 5) // "event"

    },
    "MyMainWindow\0moveObject\0\0rotateClockwise\0"
    "rotateCounterClockwise\0resetToDefault\0"
    "uploadSave\0toggleGrid\0checked\0toggleAxis\0"
    "toggleOrigin\0toggleEmulate\0showHelp\0"
    "showImplementer\0closeEvent\0QCloseEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
       9,    1,   82,    2, 0x08 /* Private */,
      10,    1,   85,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      12,    0,   91,    2, 0x08 /* Private */,
      13,    0,   92,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void MyMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->moveObject(); break;
        case 1: _t->rotateClockwise(); break;
        case 2: _t->rotateCounterClockwise(); break;
        case 3: _t->resetToDefault(); break;
        case 4: _t->uploadSave(); break;
        case 5: _t->toggleGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->toggleAxis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->toggleOrigin((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->toggleEmulate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->showHelp(); break;
        case 10: _t->showImplementer(); break;
        case 11: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyMainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MyMainWindow.data,
    qt_meta_data_MyMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MyMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
