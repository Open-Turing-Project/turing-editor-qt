/****************************************************************************
** Meta object code from reading C++ file 'qscilexerlua.h'
**
** Created: Mon Oct 31 17:15:12 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4/Qsci/qscilexerlua.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerlua.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerLua[] = {

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
      19,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerLua[] = {
    "QsciLexerLua\0\0fold\0setFoldCompact(bool)\0"
};

const QMetaObject QsciLexerLua::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerLua,
      qt_meta_data_QsciLexerLua, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerLua::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerLua::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerLua::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerLua))
        return static_cast<void*>(const_cast< QsciLexerLua*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerLua::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
