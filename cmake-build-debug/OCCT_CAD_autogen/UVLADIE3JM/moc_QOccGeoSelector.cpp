/****************************************************************************
** Meta object code from reading C++ file 'QOccGeoSelector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/QOccGeoSelector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QOccGeoSelector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QOccGeoSelector_t {
    QByteArrayData data[11];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QOccGeoSelector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QOccGeoSelector_t qt_meta_stringdata_QOccGeoSelector = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QOccGeoSelector"
QT_MOC_LITERAL(1, 16, 17), // "SelectModeChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "IVtk_SelectionMode"
QT_MOC_LITERAL(4, 54, 4), // "mode"
QT_MOC_LITERAL(5, 59, 8), // "Selected"
QT_MOC_LITERAL(6, 68, 10), // "DeSelected"
QT_MOC_LITERAL(7, 79, 18), // "OnChangeSelectMode"
QT_MOC_LITERAL(8, 98, 13), // "OnGeoSelected"
QT_MOC_LITERAL(9, 112, 21), // "OnSelectButtonToggled"
QT_MOC_LITERAL(10, 134, 21) // "OnDeleteButtonToggled"

    },
    "QOccGeoSelector\0SelectModeChanged\0\0"
    "IVtk_SelectionMode\0mode\0Selected\0"
    "DeSelected\0OnChangeSelectMode\0"
    "OnGeoSelected\0OnSelectButtonToggled\0"
    "OnDeleteButtonToggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QOccGeoSelector[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QOccGeoSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QOccGeoSelector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SelectModeChanged((*reinterpret_cast< IVtk_SelectionMode(*)>(_a[1]))); break;
        case 1: _t->Selected(); break;
        case 2: _t->DeSelected(); break;
        case 3: _t->OnChangeSelectMode(); break;
        case 4: _t->OnGeoSelected(); break;
        case 5: _t->OnSelectButtonToggled(); break;
        case 6: _t->OnDeleteButtonToggled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QOccGeoSelector::*)(IVtk_SelectionMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QOccGeoSelector::SelectModeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QOccGeoSelector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QOccGeoSelector::Selected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QOccGeoSelector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QOccGeoSelector::DeSelected)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QOccGeoSelector::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QOccGeoSelector.data,
    qt_meta_data_QOccGeoSelector,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QOccGeoSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QOccGeoSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QOccGeoSelector.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QOccGeoSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QOccGeoSelector::SelectModeChanged(IVtk_SelectionMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QOccGeoSelector::Selected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QOccGeoSelector::DeSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
