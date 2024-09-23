/****************************************************************************
** Meta object code from reading C++ file 'OccDemoMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/OccDemoMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OccDemoMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OccDemoMainWindow_t {
    QByteArrayData data[25];
    char stringdata0[390];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OccDemoMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OccDemoMainWindow_t qt_meta_stringdata_OccDemoMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "OccDemoMainWindow"
QT_MOC_LITERAL(1, 18, 20), // "signalAddNewDocument"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 6), // "isLoad"
QT_MOC_LITERAL(4, 47, 4), // "path"
QT_MOC_LITERAL(5, 52, 18), // "signalSaveDocument"
QT_MOC_LITERAL(6, 71, 18), // "signalLoadGeometry"
QT_MOC_LITERAL(7, 90, 10), // "FileFormat"
QT_MOC_LITERAL(8, 101, 6), // "format"
QT_MOC_LITERAL(9, 108, 24), // "signalChangeCurrDocument"
QT_MOC_LITERAL(10, 133, 3), // "tag"
QT_MOC_LITERAL(11, 137, 17), // "OnChangeSubWindow"
QT_MOC_LITERAL(12, 155, 14), // "QMdiSubWindow*"
QT_MOC_LITERAL(13, 170, 6), // "subWin"
QT_MOC_LITERAL(14, 177, 19), // "GetActiveViewWidget"
QT_MOC_LITERAL(15, 197, 18), // "CentralViewWidget*"
QT_MOC_LITERAL(16, 216, 14), // "AddViewDocItem"
QT_MOC_LITERAL(17, 231, 33), // "std::pair<CentralViewWidget*,..."
QT_MOC_LITERAL(18, 265, 4), // "item"
QT_MOC_LITERAL(19, 270, 10), // "UpdateView"
QT_MOC_LITERAL(20, 281, 13), // "getViewDocMap"
QT_MOC_LITERAL(21, 295, 32), // "std::map<CentralViewWidget*,int>"
QT_MOC_LITERAL(22, 328, 13), // "getDocViewMap"
QT_MOC_LITERAL(23, 342, 32), // "std::map<int,CentralViewWidget*>"
QT_MOC_LITERAL(24, 375, 14) // "UpdateTreeView"

    },
    "OccDemoMainWindow\0signalAddNewDocument\0"
    "\0isLoad\0path\0signalSaveDocument\0"
    "signalLoadGeometry\0FileFormat\0format\0"
    "signalChangeCurrDocument\0tag\0"
    "OnChangeSubWindow\0QMdiSubWindow*\0"
    "subWin\0GetActiveViewWidget\0"
    "CentralViewWidget*\0AddViewDocItem\0"
    "std::pair<CentralViewWidget*,int>\0"
    "item\0UpdateView\0getViewDocMap\0"
    "std::map<CentralViewWidget*,int>\0"
    "getDocViewMap\0std::map<int,CentralViewWidget*>\0"
    "UpdateTreeView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OccDemoMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       5,    1,   74,    2, 0x06 /* Public */,
       6,    2,   77,    2, 0x06 /* Public */,
       9,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   85,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x0a /* Public */,
      16,    1,   89,    2, 0x0a /* Public */,
      19,    0,   92,    2, 0x0a /* Public */,
      20,    0,   93,    2, 0x0a /* Public */,
      22,    0,   94,    2, 0x0a /* Public */,
      24,    0,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    4,    8,
    QMetaType::Void, QMetaType::Int,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    0x80000000 | 15,
    QMetaType::Bool, 0x80000000 | 17,   18,
    QMetaType::Void,
    0x80000000 | 21,
    0x80000000 | 23,
    QMetaType::Void,

       0        // eod
};

void OccDemoMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OccDemoMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalAddNewDocument((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->signalSaveDocument((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->signalLoadGeometry((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< FileFormat(*)>(_a[2]))); break;
        case 3: _t->signalChangeCurrDocument((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnChangeSubWindow((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 5: { CentralViewWidget* _r = _t->GetActiveViewWidget();
            if (_a[0]) *reinterpret_cast< CentralViewWidget**>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->AddViewDocItem((*reinterpret_cast< std::pair<CentralViewWidget*,int>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->UpdateView(); break;
        case 8: { std::map<CentralViewWidget*,int> _r = _t->getViewDocMap();
            if (_a[0]) *reinterpret_cast< std::map<CentralViewWidget*,int>*>(_a[0]) = std::move(_r); }  break;
        case 9: { std::map<int,CentralViewWidget*> _r = _t->getDocViewMap();
            if (_a[0]) *reinterpret_cast< std::map<int,CentralViewWidget*>*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->UpdateTreeView(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMdiSubWindow* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OccDemoMainWindow::*)(bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OccDemoMainWindow::signalAddNewDocument)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OccDemoMainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OccDemoMainWindow::signalSaveDocument)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OccDemoMainWindow::*)(const QString & , FileFormat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OccDemoMainWindow::signalLoadGeometry)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OccDemoMainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OccDemoMainWindow::signalChangeCurrDocument)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OccDemoMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<SARibbonMainWindow::staticMetaObject>(),
    qt_meta_stringdata_OccDemoMainWindow.data,
    qt_meta_data_OccDemoMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OccDemoMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OccDemoMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OccDemoMainWindow.stringdata0))
        return static_cast<void*>(this);
    return SARibbonMainWindow::qt_metacast(_clname);
}

int OccDemoMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SARibbonMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void OccDemoMainWindow::signalAddNewDocument(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OccDemoMainWindow::signalSaveDocument(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OccDemoMainWindow::signalLoadGeometry(const QString & _t1, FileFormat _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OccDemoMainWindow::signalChangeCurrDocument(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
