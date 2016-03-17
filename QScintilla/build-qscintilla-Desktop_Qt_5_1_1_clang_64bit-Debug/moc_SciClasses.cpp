/****************************************************************************
** Meta object code from reading C++ file 'SciClasses.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4Qt5/SciClasses.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SciClasses.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsciSciCallTip_t {
    QByteArrayData data[1];
    char stringdata[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciSciCallTip_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciSciCallTip_t qt_meta_stringdata_QsciSciCallTip = {
    {
QT_MOC_LITERAL(0, 0, 14)
    },
    "QsciSciCallTip\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciSciCallTip[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QsciSciCallTip::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QsciSciCallTip::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QsciSciCallTip.data,
      qt_meta_data_QsciSciCallTip,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciSciCallTip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciSciCallTip::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciSciCallTip.stringdata))
        return static_cast<void*>(const_cast< QsciSciCallTip*>(this));
    return QWidget::qt_metacast(_clname);
}

int QsciSciCallTip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_QsciSciPopup_t {
    QByteArrayData data[4];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciSciPopup_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciSciPopup_t qt_meta_stringdata_QsciSciPopup = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 3)
    },
    "QsciSciPopup\0on_triggered\0\0cmd\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciSciPopup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void QsciSciPopup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciSciPopup *_t = static_cast<QsciSciPopup *>(_o);
        switch (_id) {
        case 0: _t->on_triggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QsciSciPopup::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_QsciSciPopup.data,
      qt_meta_data_QsciSciPopup,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciSciPopup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciSciPopup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciSciPopup.stringdata))
        return static_cast<void*>(const_cast< QsciSciPopup*>(this));
    return QMenu::qt_metacast(_clname);
}

int QsciSciPopup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_QsciSciListBox_t {
    QByteArrayData data[3];
    char stringdata[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciSciListBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciSciListBox_t qt_meta_stringdata_QsciSciListBox = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 15),
QT_MOC_LITERAL(2, 31, 0)
    },
    "QsciSciListBox\0handleSelection\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciSciListBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QsciSciListBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciSciListBox *_t = static_cast<QsciSciListBox *>(_o);
        switch (_id) {
        case 0: _t->handleSelection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QsciSciListBox::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_QsciSciListBox.data,
      qt_meta_data_QsciSciListBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciSciListBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciSciListBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciSciListBox.stringdata))
        return static_cast<void*>(const_cast< QsciSciListBox*>(this));
    return QListWidget::qt_metacast(_clname);
}

int QsciSciListBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
