/****************************************************************************
** Meta object code from reading C++ file 'qscilexervhdl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4Qt5/Qsci/qscilexervhdl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexervhdl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsciLexerVHDL_t {
    QByteArrayData data[8];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciLexerVHDL_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciLexerVHDL_t qt_meta_stringdata_QsciLexerVHDL = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 15),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 4),
QT_MOC_LITERAL(4, 36, 14),
QT_MOC_LITERAL(5, 51, 13),
QT_MOC_LITERAL(6, 65, 14),
QT_MOC_LITERAL(7, 80, 20)
    },
    "QsciLexerVHDL\0setFoldComments\0\0fold\0"
    "setFoldCompact\0setFoldAtElse\0"
    "setFoldAtBegin\0setFoldAtParenthesis\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciLexerVHDL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a,
       4,    1,   42,    2, 0x0a,
       5,    1,   45,    2, 0x0a,
       6,    1,   48,    2, 0x0a,
       7,    1,   51,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void QsciLexerVHDL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciLexerVHDL *_t = static_cast<QsciLexerVHDL *>(_o);
        switch (_id) {
        case 0: _t->setFoldComments((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setFoldAtElse((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setFoldAtBegin((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setFoldAtParenthesis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QsciLexerVHDL::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerVHDL.data,
      qt_meta_data_QsciLexerVHDL,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciLexerVHDL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciLexerVHDL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerVHDL.stringdata))
        return static_cast<void*>(const_cast< QsciLexerVHDL*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerVHDL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
