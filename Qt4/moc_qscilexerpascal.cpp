/****************************************************************************
** Meta object code from reading C++ file 'qscilexerpascal.h'
**
** Created: Mon Oct 31 19:07:51 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qsci/qscilexerpascal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerpascal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerPascal[] = {

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
      22,   17,   16,   16, 0x0a,
      44,   17,   16,   16, 0x0a,
      65,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerPascal[] = {
    "QsciLexerPascal\0\0fold\0setFoldComments(bool)\0"
    "setFoldCompact(bool)\0setFoldPreprocessor(bool)\0"
};

const QMetaObject QsciLexerPascal::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerPascal,
      qt_meta_data_QsciLexerPascal, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerPascal::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerPascal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerPascal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerPascal))
        return static_cast<void*>(const_cast< QsciLexerPascal*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerPascal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFoldComments((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setFoldPreprocessor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
