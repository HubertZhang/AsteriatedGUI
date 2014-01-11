/****************************************************************************
** Meta object code from reading C++ file 'darkkiller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "players/darkkiller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'darkkiller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DarkKiller_t {
    QByteArrayData data[4];
    char stringdata[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DarkKiller_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DarkKiller_t qt_meta_stringdata_DarkKiller = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 9),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 10)
    },
    "DarkKiller\0countPlus\0\0countMinus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DarkKiller[] = {

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
       1,    0,   24,    2, 0x0a,
       3,    0,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DarkKiller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DarkKiller *_t = static_cast<DarkKiller *>(_o);
        switch (_id) {
        case 0: _t->countPlus(); break;
        case 1: _t->countMinus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DarkKiller::staticMetaObject = {
    { &CardAndSkill::staticMetaObject, qt_meta_stringdata_DarkKiller.data,
      qt_meta_data_DarkKiller,  qt_static_metacall, 0, 0}
};


const QMetaObject *DarkKiller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DarkKiller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DarkKiller.stringdata))
        return static_cast<void*>(const_cast< DarkKiller*>(this));
    return CardAndSkill::qt_metacast(_clname);
}

int DarkKiller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardAndSkill::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
