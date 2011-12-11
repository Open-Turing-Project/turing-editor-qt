/****************************************************************************
** Meta object code from reading C++ file 'qscilexervhdl.h'
**
** Created: Sun Dec 11 09:40:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QScintilla/Qt4/Qsci/qscilexervhdl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexervhdl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerVHDL[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x0a,
      42,   15,   14,   14, 0x0a,
      63,   15,   14,   14, 0x0a,
      83,   15,   14,   14, 0x0a,
     104,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerVHDL[] = {
    "QsciLexerVHDL\0\0fold\0setFoldComments(bool)\0"
    "setFoldCompact(bool)\0setFoldAtElse(bool)\0"
    "setFoldAtBegin(bool)\0setFoldAtParenthesis(bool)\0"
};

const QMetaObject QsciLexerVHDL::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerVHDL,
      qt_meta_data_QsciLexerVHDL, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerVHDL::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerVHDL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerVHDL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerVHDL))
        return static_cast<void*>(const_cast< QsciLexerVHDL*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerVHDL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFoldComments((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setFoldAtElse((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setFoldAtBegin((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: setFoldAtParenthesis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
