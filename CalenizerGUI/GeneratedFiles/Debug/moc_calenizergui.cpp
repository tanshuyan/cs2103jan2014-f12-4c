/****************************************************************************
** Meta object code from reading C++ file 'calenizergui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../calenizergui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calenizergui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CalenizerGUI_t {
    QByteArrayData data[6];
    char stringdata[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CalenizerGUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CalenizerGUI_t qt_meta_stringdata_CalenizerGUI = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 3),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 13),
QT_MOC_LITERAL(4, 32, 10),
QT_MOC_LITERAL(5, 43, 12)
    },
    "CalenizerGUI\0run\0\0checkAlphabet\0"
    "resetInput\0todayDisplay\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalenizerGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08,
       3,    0,   35,    2, 0x08,
       4,    0,   36,    2, 0x08,
       5,    0,   37,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CalenizerGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalenizerGUI *_t = static_cast<CalenizerGUI *>(_o);
        switch (_id) {
        case 0: _t->run(); break;
        case 1: _t->checkAlphabet(); break;
        case 2: _t->resetInput(); break;
        case 3: _t->todayDisplay(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CalenizerGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CalenizerGUI.data,
      qt_meta_data_CalenizerGUI,  qt_static_metacall, 0, 0}
};


const QMetaObject *CalenizerGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalenizerGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalenizerGUI.stringdata))
        return static_cast<void*>(const_cast< CalenizerGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CalenizerGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
