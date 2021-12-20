/****************************************************************************
** Meta object code from reading C++ file 'Ghost.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../lines/Ghost.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Ghost.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ghost_t {
    const uint offsetsAndSize[26];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Ghost_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Ghost_t qt_meta_stringdata_Ghost = {
    {
QT_MOC_LITERAL(0, 5), // "Ghost"
QT_MOC_LITERAL(6, 11), // "wasSelected"
QT_MOC_LITERAL(18, 0), // ""
QT_MOC_LITERAL(19, 6), // "Ghosts"
QT_MOC_LITERAL(26, 4), // "type"
QT_MOC_LITERAL(31, 11), // "MatrixPoint"
QT_MOC_LITERAL(43, 5), // "place"
QT_MOC_LITERAL(49, 13), // "wasDeselected"
QT_MOC_LITERAL(63, 10), // "wasCreated"
QT_MOC_LITERAL(74, 8), // "wasMoved"
QT_MOC_LITERAL(83, 17), // "std::vector<Node>"
QT_MOC_LITERAL(101, 4), // "road"
QT_MOC_LITERAL(106, 18) // "deleteYourselfAziz"

    },
    "Ghost\0wasSelected\0\0Ghosts\0type\0"
    "MatrixPoint\0place\0wasDeselected\0"
    "wasCreated\0wasMoved\0std::vector<Node>\0"
    "road\0deleteYourselfAziz"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ghost[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x06,    0 /* Public */,
       7,    2,   49,    2, 0x06,    3 /* Public */,
       8,    2,   54,    2, 0x06,    6 /* Public */,
       9,    2,   59,    2, 0x06,    9 /* Public */,
      12,    1,   64,    2, 0x06,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 3,   11,    4,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void Ghost::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Ghost *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->wasSelected((*reinterpret_cast< Ghosts(*)>(_a[1])),(*reinterpret_cast< MatrixPoint(*)>(_a[2]))); break;
        case 1: _t->wasDeselected((*reinterpret_cast< Ghosts(*)>(_a[1])),(*reinterpret_cast< MatrixPoint(*)>(_a[2]))); break;
        case 2: _t->wasCreated((*reinterpret_cast< Ghosts(*)>(_a[1])),(*reinterpret_cast< MatrixPoint(*)>(_a[2]))); break;
        case 3: _t->wasMoved((*reinterpret_cast< std::vector<Node>(*)>(_a[1])),(*reinterpret_cast< Ghosts(*)>(_a[2]))); break;
        case 4: _t->deleteYourselfAziz((*reinterpret_cast< MatrixPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Ghost::*)(Ghosts , MatrixPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ghost::wasSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Ghost::*)(Ghosts , MatrixPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ghost::wasDeselected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Ghost::*)(Ghosts , MatrixPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ghost::wasCreated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Ghost::*)(std::vector<Node> , Ghosts );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ghost::wasMoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Ghost::*)(MatrixPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ghost::deleteYourselfAziz)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Ghost::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Ghost.offsetsAndSize,
    qt_meta_data_Ghost,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Ghost_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Ghosts, std::false_type>, QtPrivate::TypeAndForceComplete<MatrixPoint, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Ghosts, std::false_type>, QtPrivate::TypeAndForceComplete<MatrixPoint, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Ghosts, std::false_type>, QtPrivate::TypeAndForceComplete<MatrixPoint, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Node>, std::false_type>, QtPrivate::TypeAndForceComplete<Ghosts, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<MatrixPoint, std::false_type>



>,
    nullptr
} };


const QMetaObject *Ghost::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ghost::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ghost.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ghost::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Ghost::wasSelected(Ghosts _t1, MatrixPoint _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Ghost::wasDeselected(Ghosts _t1, MatrixPoint _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Ghost::wasCreated(Ghosts _t1, MatrixPoint _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Ghost::wasMoved(std::vector<Node> _t1, Ghosts _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Ghost::deleteYourselfAziz(MatrixPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
