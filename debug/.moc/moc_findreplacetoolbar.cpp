/****************************************************************************
** Meta object code from reading C++ file 'findreplacetoolbar.h'
**
** Created: Sun Dec 11 09:39:50 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TuringEditor/findreplacetoolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findreplacetoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FindReplaceToolbar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   20,   19,   19, 0x05,
      43,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FindReplaceToolbar[] = {
    "FindReplaceToolbar\0\0findText\0find(QString)\0"
    "findNext()\0findNextPushed()\0"
};

const QMetaObject FindReplaceToolbar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_FindReplaceToolbar,
      qt_meta_data_FindReplaceToolbar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FindReplaceToolbar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FindReplaceToolbar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FindReplaceToolbar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FindReplaceToolbar))
        return static_cast<void*>(const_cast< FindReplaceToolbar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int FindReplaceToolbar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: find((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: findNext(); break;
        case 2: findNextPushed(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FindReplaceToolbar::find(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FindReplaceToolbar::findNext()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
