/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Nov 5 10:49:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x0a,
      77,   38,   11,   11, 0x0a,
     106,   11,   11,   11, 0x0a,
     125,  117,   11,   11, 0x0a,
     177,  142,   11,   11, 0x0a,
     215,   11,   11,   11, 0x08,
     225,   11,   11,   11, 0x08,
     237,   11,  232,   11, 0x08,
     244,   11,  232,   11, 0x08,
     253,   11,   11,   11, 0x08,
     261,   11,   11,   11, 0x08,
     283,   11,   11,   11, 0x08,
     296,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0findText\0findAll(QString)\0"
    "findText,CaseSensitive,regex,wholeWord\0"
    "find(QString,bool,bool,bool)\0findNext()\0"
    "repText\0replace(QString)\0"
    "findText,repText,regex,greedyRegex\0"
    "replaceAll(QString,QString,bool,bool)\0"
    "newFile()\0open()\0bool\0save()\0saveAs()\0"
    "about()\0documentWasModified()\0"
    "lightTheme()\0darkTheme()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: findAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: find((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: findNext(); break;
        case 3: replace((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: replaceAll((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 5: newFile(); break;
        case 6: open(); break;
        case 7: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: about(); break;
        case 10: documentWasModified(); break;
        case 11: lightTheme(); break;
        case 12: darkTheme(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
