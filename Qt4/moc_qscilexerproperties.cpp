/****************************************************************************
** Meta object code from reading C++ file 'qscilexerproperties.h'
**
** Created: Mon Oct 31 19:07:55 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qsci/qscilexerproperties.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerproperties.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerProperties[] = {

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
      26,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerProperties[] = {
    "QsciLexerProperties\0\0fold\0"
    "setFoldCompact(bool)\0"
};

const QMetaObject QsciLexerProperties::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerProperties,
      qt_meta_data_QsciLexerProperties, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerProperties::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerProperties::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerProperties::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerProperties))
        return static_cast<void*>(const_cast< QsciLexerProperties*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerProperties::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
