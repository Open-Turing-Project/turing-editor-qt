/****************************************************************************
** Meta object code from reading C++ file 'qscilexercmake.h'
**
** Created: Mon Oct 31 17:15:02 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4/Qsci/qscilexercmake.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexercmake.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerCMake[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerCMake[] = {
    "QsciLexerCMake\0\0fold\0setFoldAtElse(bool)\0"
};

const QMetaObject QsciLexerCMake::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerCMake,
      qt_meta_data_QsciLexerCMake, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerCMake::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerCMake::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerCMake::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerCMake))
        return static_cast<void*>(const_cast< QsciLexerCMake*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerCMake::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFoldAtElse((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
