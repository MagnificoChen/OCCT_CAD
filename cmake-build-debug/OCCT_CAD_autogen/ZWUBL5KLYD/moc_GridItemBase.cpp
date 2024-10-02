/****************************************************************************
** Meta object code from reading C++ file 'GridItemBase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/Dialog/Components/GridItemBase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GridItemBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GridItemBase_t {
    QByteArrayData data[8];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GridItemBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GridItemBase_t qt_meta_stringdata_GridItemBase = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GridItemBase"
QT_MOC_LITERAL(1, 13, 20), // "OnToolButton1Clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 20), // "OnToolButton2Clicked"
QT_MOC_LITERAL(5, 62, 19), // "OnMainButtonToggled"
QT_MOC_LITERAL(6, 82, 10), // "EnableItem"
QT_MOC_LITERAL(7, 93, 9) // "isEnabled"

    },
    "GridItemBase\0OnToolButton1Clicked\0\0"
    "index\0OnToolButton2Clicked\0"
    "OnMainButtonToggled\0EnableItem\0isEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GridItemBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x0a /* Public */,
       6,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Bool,

       0        // eod
};

void GridItemBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GridItemBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnToolButton1Clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnToolButton2Clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnMainButtonToggled(); break;
        case 3: _t->EnableItem((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { bool _r = _t->isEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GridItemBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GridItemBase.data,
    qt_meta_data_GridItemBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GridItemBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GridItemBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GridItemBase.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GridItemBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
