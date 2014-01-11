/****************************************************************************
** Meta object code from reading C++ file 'uuz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "players/uuz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uuz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UUZ_t {
    QByteArrayData data[12];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UUZ_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UUZ_t qt_meta_stringdata_UUZ = {
    {
QT_MOC_LITERAL(0, 0, 3),
QT_MOC_LITERAL(1, 4, 12),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 11),
QT_MOC_LITERAL(4, 30, 11),
QT_MOC_LITERAL(5, 42, 13),
QT_MOC_LITERAL(6, 56, 8),
QT_MOC_LITERAL(7, 65, 10),
QT_MOC_LITERAL(8, 76, 8),
QT_MOC_LITERAL(9, 85, 9),
QT_MOC_LITERAL(10, 95, 10),
QT_MOC_LITERAL(11, 106, 11)
    },
    "UUZ\0magicSetZero\0\0magicSetOne\0magicSetTwo\0"
    "magicSetThree\0skillset\0skillClear\0"
    "soulPlus\0soulMinus\0mirrorPlus\0mirrorMinus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UUZ[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a,
       3,    0,   65,    2, 0x0a,
       4,    0,   66,    2, 0x0a,
       5,    0,   67,    2, 0x0a,
       6,    0,   68,    2, 0x0a,
       7,    0,   69,    2, 0x0a,
       8,    0,   70,    2, 0x0a,
       9,    0,   71,    2, 0x0a,
      10,    0,   72,    2, 0x0a,
      11,    0,   73,    2, 0x0a,

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

       0        // eod
};

void UUZ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UUZ *_t = static_cast<UUZ *>(_o);
        switch (_id) {
        case 0: _t->magicSetZero(); break;
        case 1: _t->magicSetOne(); break;
        case 2: _t->magicSetTwo(); break;
        case 3: _t->magicSetThree(); break;
        case 4: _t->skillset(); break;
        case 5: _t->skillClear(); break;
        case 6: _t->soulPlus(); break;
        case 7: _t->soulMinus(); break;
        case 8: _t->mirrorPlus(); break;
        case 9: _t->mirrorMinus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UUZ::staticMetaObject = {
    { &CardAndSkill::staticMetaObject, qt_meta_stringdata_UUZ.data,
      qt_meta_data_UUZ,  qt_static_metacall, 0, 0}
};


const QMetaObject *UUZ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UUZ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UUZ.stringdata))
        return static_cast<void*>(const_cast< UUZ*>(this));
    return CardAndSkill::qt_metacast(_clname);
}

int UUZ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardAndSkill::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
