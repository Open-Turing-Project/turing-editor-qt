/****************************************************************************
** Meta object code from reading C++ file 'qscilexerd.h'
**
** Created: Mon Oct 31 17:15:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4/Qsci/qscilexerd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerD[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,
      37,   12,   11,   11, 0x0a,
      59,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerD[] = {
    "QsciLexerD\0\0fold\0setFoldAtElse(bool)\0"
    "setFoldComments(bool)\0setFoldCompact(bool)\0"
};

const QMetaObject QsciLexerD::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerD,
      qt_meta_data_QsciLexerD, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerD))
        return static_cast<void*>(const_cast< QsciLexerD*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFoldAtElse((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setFoldComments((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
