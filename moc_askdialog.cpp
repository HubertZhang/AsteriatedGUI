/****************************************************************************
** Meta object code from reading C++ file 'askdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "askdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'askdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AskDialog_t {
    QByteArrayData data[9];
    char stringdata[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AskDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AskDialog_t qt_meta_stringdata_AskDialog = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 11),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 17),
QT_MOC_LITERAL(4, 41, 16),
QT_MOC_LITERAL(5, 58, 18),
QT_MOC_LITERAL(6, 77, 18),
QT_MOC_LITERAL(7, 96, 13),
QT_MOC_LITERAL(8, 110, 13)
    },
    "AskDialog\0activateSig\0\0sendMessageSpeSig\0"
    "std::vector<int>\0sendMessageWeakSig\0"
    "sendMessageCureSig\0ensureClicked\0"
    "cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AskDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06,
       3,    1,   49,    2, 0x06,
       5,    1,   52,    2, 0x06,
       6,    1,   55,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    0,   58,    2, 0x0a,
       8,    0,   59,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    2,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AskDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AskDialog *_t = static_cast<AskDialog *>(_o);
        switch (_id) {
        case 0: _t->activateSig((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->sendMessageSpeSig((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        case 2: _t->sendMessageWeakSig((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        case 3: _t->sendMessageCureSig((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        case 4: _t->ensureClicked(); break;
        case 5: _t->cancelClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AskDialog::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AskDialog::activateSig)) {
                *result = 0;
            }
        }
        {
            typedef void (AskDialog::*_t)(std::vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AskDialog::sendMessageSpeSig)) {
                *result = 1;
            }
        }
        {
            typedef void (AskDialog::*_t)(std::vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AskDialog::sendMessageWeakSig)) {
                *result = 2;
            }
        }
        {
            typedef void (AskDialog::*_t)(std::vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AskDialog::sendMessageCureSig)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject AskDialog::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_AskDialog.data,
      qt_meta_data_AskDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *AskDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AskDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskDialog.stringdata))
        return static_cast<void*>(const_cast< AskDialog*>(this));
    return QLabel::qt_metacast(_clname);
}

int AskDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AskDialog::activateSig(bool _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AskDialog::sendMessageSpeSig(std::vector<int> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AskDialog::sendMessageWeakSig(std::vector<int> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AskDialog::sendMessageCureSig(std::vector<int> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_WeakDialog_t {
    QByteArrayData data[4];
    char stringdata[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_WeakDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_WeakDialog_t qt_meta_stringdata_WeakDialog = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 13)
    },
    "WeakDialog\0ensureClicked\0\0cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeakDialog[] = {

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

void WeakDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WeakDialog *_t = static_cast<WeakDialog *>(_o);
        switch (_id) {
        case 0: _t->ensureClicked(); break;
        case 1: _t->cancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WeakDialog::staticMetaObject = {
    { &AskDialog::staticMetaObject, qt_meta_stringdata_WeakDialog.data,
      qt_meta_data_WeakDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *WeakDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeakDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WeakDialog.stringdata))
        return static_cast<void*>(const_cast< WeakDialog*>(this));
    return AskDialog::qt_metacast(_clname);
}

int WeakDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ActiveDialog_t {
    QByteArrayData data[4];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ActiveDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ActiveDialog_t qt_meta_stringdata_ActiveDialog = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 13)
    },
    "ActiveDialog\0ensureClicked\0\0cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ActiveDialog[] = {

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

void ActiveDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ActiveDialog *_t = static_cast<ActiveDialog *>(_o);
        switch (_id) {
        case 0: _t->ensureClicked(); break;
        case 1: _t->cancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ActiveDialog::staticMetaObject = {
    { &AskDialog::staticMetaObject, qt_meta_stringdata_ActiveDialog.data,
      qt_meta_data_ActiveDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *ActiveDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ActiveDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActiveDialog.stringdata))
        return static_cast<void*>(const_cast< ActiveDialog*>(this));
    return AskDialog::qt_metacast(_clname);
}

int ActiveDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_CureDialog_t {
    QByteArrayData data[4];
    char stringdata[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CureDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CureDialog_t qt_meta_stringdata_CureDialog = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 13)
    },
    "CureDialog\0ensureClicked\0\0cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CureDialog[] = {

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

void CureDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CureDialog *_t = static_cast<CureDialog *>(_o);
        switch (_id) {
        case 0: _t->ensureClicked(); break;
        case 1: _t->cancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CureDialog::staticMetaObject = {
    { &AskDialog::staticMetaObject, qt_meta_stringdata_CureDialog.data,
      qt_meta_data_CureDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *CureDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CureDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CureDialog.stringdata))
        return static_cast<void*>(const_cast< CureDialog*>(this));
    return AskDialog::qt_metacast(_clname);
}

int CureDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_NumberDialog_t {
    QByteArrayData data[4];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NumberDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NumberDialog_t qt_meta_stringdata_NumberDialog = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 13)
    },
    "NumberDialog\0ensureClicked\0\0cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NumberDialog[] = {

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

void NumberDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NumberDialog *_t = static_cast<NumberDialog *>(_o);
        switch (_id) {
        case 0: _t->ensureClicked(); break;
        case 1: _t->cancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NumberDialog::staticMetaObject = {
    { &AskDialog::staticMetaObject, qt_meta_stringdata_NumberDialog.data,
      qt_meta_data_NumberDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *NumberDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NumberDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NumberDialog.stringdata))
        return static_cast<void*>(const_cast< NumberDialog*>(this));
    return AskDialog::qt_metacast(_clname);
}

int NumberDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_SpecialDialog_t {
    QByteArrayData data[4];
    char stringdata[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SpecialDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SpecialDialog_t qt_meta_stringdata_SpecialDialog = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 13),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 13)
    },
    "SpecialDialog\0ensureClicked\0\0cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpecialDialog[] = {

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

void SpecialDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpecialDialog *_t = static_cast<SpecialDialog *>(_o);
        switch (_id) {
        case 0: _t->ensureClicked(); break;
        case 1: _t->cancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SpecialDialog::staticMetaObject = {
    { &AskDialog::staticMetaObject, qt_meta_stringdata_SpecialDialog.data,
      qt_meta_data_SpecialDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *SpecialDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpecialDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpecialDialog.stringdata))
        return static_cast<void*>(const_cast< SpecialDialog*>(this));
    return AskDialog::qt_metacast(_clname);
}

int SpecialDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskDialog::qt_metacall(_c, _id, _a);
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
