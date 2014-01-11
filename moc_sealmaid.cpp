/****************************************************************************
** Meta object code from reading C++ file 'sealmaid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "players/sealmaid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sealmaid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SealMaid_t {
    QByteArrayData data[9];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SealMaid_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SealMaid_t qt_meta_stringdata_SealMaid = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 8),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 12),
QT_MOC_LITERAL(4, 32, 11),
QT_MOC_LITERAL(5, 44, 11),
QT_MOC_LITERAL(6, 56, 10),
QT_MOC_LITERAL(7, 67, 15),
QT_MOC_LITERAL(8, 83, 17)
    },
    "SealMaid\0skillset\0\0magicSetZero\0"
    "magicSetOne\0magicSetTwo\0skillClear\0"
    "reminiscenceSet\0reminiscenceReset\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SealMaid[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a,
       3,    0,   50,    2, 0x0a,
       4,    0,   51,    2, 0x0a,
       5,    0,   52,    2, 0x0a,
       6,    0,   53,    2, 0x0a,
       7,    0,   54,    2, 0x0a,
       8,    0,   55,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SealMaid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SealMaid *_t = static_cast<SealMaid *>(_o);
        switch (_id) {
        case 0: _t->skillset(); break;
        case 1: _t->magicSetZero(); break;
        case 2: _t->magicSetOne(); break;
        case 3: _t->magicSetTwo(); break;
        case 4: _t->skillClear(); break;
        case 5: _t->reminiscenceSet(); break;
        case 6: _t->reminiscenceReset(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SealMaid::staticMetaObject = {
    { &CardAndSkill::staticMetaObject, qt_meta_stringdata_SealMaid.data,
      qt_meta_data_SealMaid,  qt_static_metacall, 0, 0}
};


const QMetaObject *SealMaid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SealMaid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SealMaid.stringdata))
        return static_cast<void*>(const_cast< SealMaid*>(this));
    return CardAndSkill::qt_metacast(_clname);
}

int SealMaid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardAndSkill::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
