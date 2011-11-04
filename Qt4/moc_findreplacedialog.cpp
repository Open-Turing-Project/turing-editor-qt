/****************************************************************************
** Meta object code from reading C++ file 'findreplacedialog.h'
**
** Created: Fri Nov 4 19:49:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "findreplacedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findreplacedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FindReplaceDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   19,   18,   18, 0x05,
      60,   41,   18,   18, 0x05,
      79,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      90,   18,   18,   18, 0x08,
     106,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FindReplaceDialog[] = {
    "FindReplaceDialog\0\0text\0findAll(QString)\0"
    "text,caseSensitive\0find(QString,bool)\0"
    "findNext()\0findAllPushed()\0findNextPushed()\0"
};

const QMetaObject FindReplaceDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FindReplaceDialog,
      qt_meta_data_FindReplaceDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FindReplaceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FindReplaceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FindReplaceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FindReplaceDialog))
        return static_cast<void*>(const_cast< FindReplaceDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int FindReplaceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: findAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: find((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: findNext(); break;
        case 3: findAllPushed(); break;
        case 4: findNextPushed(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FindReplaceDialog::findAll(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FindReplaceDialog::find(QString _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FindReplaceDialog::findNext()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
