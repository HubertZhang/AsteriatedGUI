/****************************************************************************
** Meta object code from reading C++ file 'priestmaid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "players/priestmaid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'priestmaid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PriestMaid_t {
    QByteArrayData data[17];
    char stringdata[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PriestMaid_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PriestMaid_t qt_meta_stringdata_PriestMaid = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 11),
QT_MOC_LITERAL(4, 37, 11),
QT_MOC_LITERAL(5, 49, 13),
QT_MOC_LITERAL(6, 63, 8),
QT_MOC_LITERAL(7, 72, 10),
QT_MOC_LITERAL(8, 83, 9),
QT_MOC_LITERAL(9, 93, 10),
QT_MOC_LITERAL(10, 104, 8),
QT_MOC_LITERAL(11, 113, 9),
QT_MOC_LITERAL(12, 123, 10),
QT_MOC_LITERAL(13, 134, 11),
QT_MOC_LITERAL(14, 146, 13),
QT_MOC_LITERAL(15, 160, 8),
QT_MOC_LITERAL(16, 169, 9)
    },
    "PriestMaid\0magicSetZero\0\0magicSetOne\0"
    "magicSetTwo\0magicSetThree\0skillset\0"
    "skillClear\0magicPlus\0magicMinus\0"
    "zonePlus\0zoneMinus\0waterPhase\0contractSet\0"
    "contractReset\0curePlus\0cureMinus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PriestMaid[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a,
       3,    0,   90,    2, 0x0a,
       4,    0,   91,    2, 0x0a,
       5,    0,   92,    2, 0x0a,
       6,    0,   93,    2, 0x0a,
       7,    0,   94,    2, 0x0a,
       8,    0,   95,    2, 0x0a,
       9,    0,   96,    2, 0x0a,
      10,    0,   97,    2, 0x0a,
      11,    0,   98,    2, 0x0a,
      12,    0,   99,    2, 0x0a,
      13,    0,  100,    2, 0x0a,
      14,    0,  101,    2, 0x0a,
      15,    0,  102,    2, 0x0a,
      16,    0,  103,    2, 0x0a,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PriestMaid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PriestMaid *_t = static_cast<PriestMaid *>(_o);
        switch (_id) {
        case 0: _t->magicSetZero(); break;
        case 1: _t->magicSetOne(); break;
        case 2: _t->magicSetTwo(); break;
        case 3: _t->magicSetThree(); break;
        case 4: _t->skillset(); break;
        case 5: _t->skillClear(); break;
        case 6: _t->magicPlus(); break;
        case 7: _t->magicMinus(); break;
        case 8: _t->zonePlus(); break;
        case 9: _t->zoneMinus(); break;
        case 10: _t->waterPhase(); break;
        case 11: _t->contractSet(); break;
        case 12: _t->contractReset(); break;
        case 13: _t->curePlus(); break;
        case 14: _t->cureMinus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PriestMaid::staticMetaObject = {
    { &CardAndSkill::staticMetaObject, qt_meta_stringdata_PriestMaid.data,
      qt_meta_data_PriestMaid,  qt_static_metacall, 0, 0}
};


const QMetaObject *PriestMaid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PriestMaid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PriestMaid.stringdata))
        return static_cast<void*>(const_cast< PriestMaid*>(this));
    return CardAndSkill::qt_metacast(_clname);
}

int PriestMaid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardAndSkill::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
