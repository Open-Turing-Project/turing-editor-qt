/****************************************************************************
** Meta object code from reading C++ file 'qsciapis.h'
**
** Created: Sun May 5 09:37:46 2013
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt4Qt5/Qsci/qsciapis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qsciapis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsciAPIs_t {
    QByteArrayData data[5];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsciAPIs_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsciAPIs_t qt_meta_stringdata_QsciAPIs = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 23),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 21),
QT_MOC_LITERAL(4, 56, 22)
    },
    "QsciAPIs\0apiPreparationCancelled\0\0"
    "apiPreparationStarted\0apiPreparationFinished\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsciAPIs[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x05,
       3,    0,   30,    2, 0x05,
       4,    0,   31,    2, 0x05,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QsciAPIs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsciAPIs *_t = static_cast<QsciAPIs *>(_o);
        switch (_id) {
        case 0: _t->apiPreparationCancelled(); break;
        case 1: _t->apiPreparationStarted(); break;
        case 2: _t->apiPreparationFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QsciAPIs::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QsciAPIs::apiPreparationCancelled)) {
                *result = 0;
            }
        }
        {
            typedef void (QsciAPIs::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QsciAPIs::apiPreparationStarted)) {
                *result = 1;
            }
        }
        {
            typedef void (QsciAPIs::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QsciAPIs::apiPreparationFinished)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QsciAPIs::staticMetaObject = {
    { &QsciAbstractAPIs::staticMetaObject, qt_meta_stringdata_QsciAPIs.data,
      qt_meta_data_QsciAPIs,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsciAPIs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsciAPIs::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciAPIs.stringdata))
        return static_cast<void*>(const_cast< QsciAPIs*>(this));
    return QsciAbstractAPIs::qt_metacast(_clname);
}

int QsciAPIs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciAbstractAPIs::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QsciAPIs::apiPreparationCancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QsciAPIs::apiPreparationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QsciAPIs::apiPreparationFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
