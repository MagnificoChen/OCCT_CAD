/****************************************************************************
** Meta object code from reading C++ file 'QDocumentManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/QDocumentManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QDocumentManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QDocumentManager_t {
    QByteArrayData data[17];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDocumentManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDocumentManager_t qt_meta_stringdata_QDocumentManager = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QDocumentManager"
QT_MOC_LITERAL(1, 17, 16), // "signalUpdateView"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 13), // "OnNewDocument"
QT_MOC_LITERAL(4, 49, 6), // "isLoad"
QT_MOC_LITERAL(5, 56, 8), // "filePath"
QT_MOC_LITERAL(6, 65, 12), // "SaveDocument"
QT_MOC_LITERAL(7, 78, 12), // "LoadGeometry"
QT_MOC_LITERAL(8, 91, 10), // "FileFormat"
QT_MOC_LITERAL(9, 102, 6), // "format"
QT_MOC_LITERAL(10, 109, 16), // "OnChangeDocument"
QT_MOC_LITERAL(11, 126, 3), // "tag"
QT_MOC_LITERAL(12, 130, 20), // "_getUniqueObjectName"
QT_MOC_LITERAL(13, 151, 11), // "std::string"
QT_MOC_LITERAL(14, 163, 6), // "prefix"
QT_MOC_LITERAL(15, 170, 30), // "std::map<QString,TopoDS_Shape>"
QT_MOC_LITERAL(16, 201, 9) // "objectMap"

    },
    "QDocumentManager\0signalUpdateView\0\0"
    "OnNewDocument\0isLoad\0filePath\0"
    "SaveDocument\0LoadGeometry\0FileFormat\0"
    "format\0OnChangeDocument\0tag\0"
    "_getUniqueObjectName\0std::string\0"
    "prefix\0std::map<QString,TopoDS_Shape>\0"
    "objectMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDocumentManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   45,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       7,    2,   53,    2, 0x0a /* Public */,
      10,    1,   58,    2, 0x0a /* Public */,
      12,    2,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::Bool, QMetaType::QString,    4,    5,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 8,    5,    9,
    QMetaType::Bool, QMetaType::Int,   11,
    0x80000000 | 13, 0x80000000 | 13, 0x80000000 | 15,   14,   16,

       0        // eod
};

void QDocumentManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QDocumentManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateView(); break;
        case 1: { bool _r = _t->OnNewDocument((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->SaveDocument((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->LoadGeometry((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< FileFormat(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->OnChangeDocument((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { std::string _r = _t->_getUniqueObjectName((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::map<QString,TopoDS_Shape>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QDocumentManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QDocumentManager::signalUpdateView)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QDocumentManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QDocumentManager.data,
    qt_meta_data_QDocumentManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QDocumentManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDocumentManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDocumentManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QDocumentManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void QDocumentManager::signalUpdateView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
