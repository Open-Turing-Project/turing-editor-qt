/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Dec 11 09:39:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TuringEditor/mainwindow.h"
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
      18,   14, // methods
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
     235,  215,   11,   11, 0x0a,
     283,  266,   11,   11, 0x2a,
     322,  310,   11,   11, 0x2a,
     345,   11,   11,   11, 0x0a,
     359,   11,   11,   11, 0x0a,
     377,   11,   11,   11, 0x08,
     387,   11,   11,   11, 0x08,
     399,   11,  394,   11, 0x08,
     406,   11,  394,   11, 0x08,
     415,   11,   11,   11, 0x08,
     423,   11,   11,   11, 0x08,
     445,   11,   11,   11, 0x08,
     458,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0findText\0findAll(QString)\0"
    "findText,CaseSensitive,regex,wholeWord\0"
    "find(QString,bool,bool,bool)\0findNext()\0"
    "repText\0replace(QString)\0"
    "findText,repText,regex,greedyRegex\0"
    "replaceAll(QString,QString,bool,bool)\0"
    "line,errMsg,from,to\0showError(int,QString,int,int)\0"
    "line,errMsg,from\0showError(int,QString,int)\0"
    "line,errMsg\0showError(int,QString)\0"
    "clearErrors()\0clearEverything()\0"
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
        case 5: showError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: showError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: showError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: clearErrors(); break;
        case 9: clearEverything(); break;
        case 10: newFile(); break;
        case 11: open(); break;
        case 12: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: about(); break;
        case 15: documentWasModified(); break;
        case 16: lightTheme(); break;
        case 17: darkTheme(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
