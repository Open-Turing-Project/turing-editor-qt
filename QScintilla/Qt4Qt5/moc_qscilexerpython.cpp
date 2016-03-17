/****************************************************************************
** Meta object code from reading C++ file 'qscilexerpython.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qsci/qscilexerpython.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerpython.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsciLexerPython_t {
    QByteArrayData data[8];
    char stringdata[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciLexerPython_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciLexerPython_t qt_meta_stringdata_QsciLexerPython = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 15),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 4),
QT_MOC_LITERAL(4, 38, 13),
QT_MOC_LITERAL(5, 52, 21),
QT_MOC_LITERAL(6, 74, 35),
QT_MOC_LITERAL(7, 110, 4)
    },
    "QsciLexerPython\0setFoldComments\0\0fold\0"
    "setFoldQuotes\0setIndentationWarning\0"
    "QsciLexerPython::IndentationWarning\0"
    "warn\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciLexerPython[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a,
       4,    1,   32,    2, 0x0a,
       5,    1,   35,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void QsciLexerPython::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciLexerPython *_t = static_cast<QsciLexerPython *>(_o);
        switch (_id) {
        case 0: _t->setFoldComments((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setFoldQuotes((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setIndentationWarning((*reinterpret_cast< QsciLexerPython::IndentationWarning(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QsciLexerPython::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerPython.data,
      qt_meta_data_QsciLexerPython,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciLexerPython::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciLexerPython::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerPython.stringdata))
        return static_cast<void*>(const_cast< QsciLexerPython*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerPython::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
