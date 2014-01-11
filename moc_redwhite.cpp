/****************************************************************************
** Meta object code from reading C++ file 'redwhite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "players/redwhite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'redwhite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RedWhite_t {
    QByteArrayData data[13];
    char stringdata[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_RedWhite_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_RedWhite_t qt_meta_stringdata_RedWhite = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 12),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 11),
QT_MOC_LITERAL(4, 35, 11),
QT_MOC_LITERAL(5, 47, 13),
QT_MOC_LITERAL(6, 61, 8),
QT_MOC_LITERAL(7, 70, 10),
QT_MOC_LITERAL(8, 81, 9),
QT_MOC_LITERAL(9, 91, 10),
QT_MOC_LITERAL(10, 102, 9),
QT_MOC_LITERAL(11, 112, 10),
QT_MOC_LITERAL(12, 123, 8)
    },
    "RedWhite\0magicSetZero\0\0magicSetOne\0"
    "magicSetTwo\0magicSetThree\0skillset\0"
    "skillClear\0bloodPlus\0bloodMinus\0"
    "cursePlus\0curseMinus\0bloodSet\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RedWhite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a,
       3,    0,   70,    2, 0x0a,
       4,    0,   71,    2, 0x0a,
       5,    0,   72,    2, 0x0a,
       6,    0,   73,    2, 0x0a,
       7,    0,   74,    2, 0x0a,
       8,    0,   75,    2, 0x0a,
       9,    0,   76,    2, 0x0a,
      10,    0,   77,    2, 0x0a,
      11,    0,   78,    2, 0x0a,
      12,    0,   79,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RedWhite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RedWhite *_t = static_cast<RedWhite *>(_o);
        switch (_id) {
        case 0: _t->magicSetZero(); break;
        case 1: _t->magicSetOne(); break;
        case 2: _t->magicSetTwo(); break;
        case 3: _t->magicSetThree(); break;
        case 4: _t->skillset(); break;
        case 5: _t->skillClear(); break;
        case 6: _t->bloodPlus(); break;
        case 7: _t->bloodMinus(); break;
        case 8: _t->cursePlus(); break;
        case 9: _t->curseMinus(); break;
        case 10: _t->bloodSet(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RedWhite::staticMetaObject = {
    { &CardAndSkill::staticMetaObject, qt_meta_stringdata_RedWhite.data,
      qt_meta_data_RedWhite,  qt_static_metacall, 0, 0}
};


const QMetaObject *RedWhite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RedWhite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RedWhite.stringdata))
        return static_cast<void*>(const_cast< RedWhite*>(this));
    return CardAndSkill::qt_metacast(_clname);
}

int RedWhite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardAndSkill::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
