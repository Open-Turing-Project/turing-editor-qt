/****************************************************************************
** Meta object code from reading C++ file 'qscilexerproperties.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qsci/qscilexerproperties.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerproperties.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsciLexerProperties_t {
    QByteArrayData data[4];
    char stringdata[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciLexerProperties_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciLexerProperties_t qt_meta_stringdata_QsciLexerProperties = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 14),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 4)
    },
    "QsciLexerProperties\0setFoldCompact\0\0"
    "fold\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciLexerProperties[] = {

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
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void QsciLexerProperties::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciLexerProperties *_t = static_cast<QsciLexerProperties *>(_o);
        switch (_id) {
        case 0: _t->setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QsciLexerProperties::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerProperties.data,
      qt_meta_data_QsciLexerProperties,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciLexerProperties::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciLexerProperties::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerProperties.stringdata))
        return static_cast<void*>(const_cast< QsciLexerProperties*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerProperties::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
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
