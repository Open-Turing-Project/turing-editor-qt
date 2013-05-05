/****************************************************************************
** Meta object code from reading C++ file 'qscimacro.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4Qt5/Qsci/qscimacro.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscimacro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsciMacro_t {
    QByteArrayData data[9];
    char stringdata[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciMacro_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciMacro_t qt_meta_stringdata_QsciMacro = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 4),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 14),
QT_MOC_LITERAL(4, 31, 12),
QT_MOC_LITERAL(5, 44, 6),
QT_MOC_LITERAL(6, 51, 3),
QT_MOC_LITERAL(7, 55, 6),
QT_MOC_LITERAL(8, 62, 6)
    },
    "QsciMacro\0play\0\0startRecording\0"
    "endRecording\0record\0msg\0wParam\0lParam\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciMacro[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a,
       3,    0,   35,    2, 0x0a,
       4,    0,   36,    2, 0x0a,
       5,    3,   37,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::ULong, QMetaType::VoidStar,    6,    7,    8,

       0        // eod
};

void QsciMacro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciMacro *_t = static_cast<QsciMacro *>(_o);
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->startRecording(); break;
        case 2: _t->endRecording(); break;
        case 3: _t->record((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject QsciMacro::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QsciMacro.data,
      qt_meta_data_QsciMacro,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciMacro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciMacro::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciMacro.stringdata))
        return static_cast<void*>(const_cast< QsciMacro*>(this));
    return QObject::qt_metacast(_clname);
}

int QsciMacro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
