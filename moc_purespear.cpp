/****************************************************************************
** Meta object code from reading C++ file 'purespear.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "players/purespear.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'purespear.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PureSpear_t {
    QByteArrayData data[7];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PureSpear_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PureSpear_t qt_meta_stringdata_PureSpear = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 12),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 11),
QT_MOC_LITERAL(4, 36, 11),
QT_MOC_LITERAL(5, 48, 8),
QT_MOC_LITERAL(6, 57, 10)
    },
    "PureSpear\0magicSetZero\0\0magicSetOne\0"
    "magicSetTwo\0skillset\0skillClear\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PureSpear[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a,
       3,    0,   40,    2, 0x0a,
       4,    0,   41,    2, 0x0a,
       5,    0,   42,    2, 0x0a,
       6,    0,   43,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PureSpear::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PureSpear *_t = static_cast<PureSpear *>(_o);
        switch (_id) {
        case 0: _t->magicSetZero(); break;
        case 1: _t->magicSetOne(); break;
        case 2: _t->magicSetTwo(); break;
        case 3: _t->skillset(); break;
        case 4: _t->skillClear(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PureSpear::staticMetaObject = {
    { &CardAndSkill::staticMetaObject, qt_meta_stringdata_PureSpear.data,
      qt_meta_data_PureSpear,  qt_static_metacall, 0, 0}
};


const QMetaObject *PureSpear::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PureSpear::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PureSpear.stringdata))
        return static_cast<void*>(const_cast< PureSpear*>(this));
    return CardAndSkill::qt_metacast(_clname);
}

int PureSpear::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardAndSkill::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
