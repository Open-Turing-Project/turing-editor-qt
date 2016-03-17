# Open Turing Version

CURRENT_VERSION = 2.0.0 alpha
VERSTR = '\\"$${CURRENT_VERSION}\\"'  # place quotes around the version string
DEFINES = VERSION_STRING=\"$${VERSTR}\" # create a VER macro containing the version string

# files used in the running process
# file is found in support/bin/TuringEXEProlog.exe
# of the main OpenTuring distribution
HELP_FILE = support/help/TuringDoc.chm

HELP_FILE_STR = '\\"$${HELP_FILE}\\"'
DEFINES += HELP_FILE_PATH=\"$${HELP_FILE_STR}\"

#TEMPLATE = lib
TARGET = OpenTuring
CONFIG += qt thread
QT += webkit widgets webkitwidgets
release {
    CONFIG += warn_off
} else {
    CONFIG += debug
}
#macx {
#    QMAKE_POST_LINK = install_name_tool -change libqscintilla2.9.dylib $$[QT_INSTALL_LIBS]/libqscintilla2.9.dylib $(TARGET)
#}

LIBS += -L$$[QT_INSTALL_LIBS] -lqscintilla2 -headerpad_max_install_names
#QMAKE_LFLAGS += -headerpad_max_install_names
INCLUDEPATH = ./TuringEditor ./TuringEditor/resources
RESOURCES = ./TuringEditor/turing.qrc
DEFINES += QT
ICON = OpenTuringIcon.icns

RC_FILE = TuringEditor/resources/turing.rc

CONFIG(test_editor) {
    DESTDIR = test/build
    OBJECTS_DIR = test/build/obj
    MOC_DIR = test/build/moc
    RCC_DIR = test/build/rcc
    UI_DIR = test/build/ui
} else:debug {
    DESTDIR = ./debug
    OBJECTS_DIR = ./debug/build/obj
    MOC_DIR = ./debug/build/moc
    RCC_DIR = ./debug/build/rcc
    UI_DIR = ./debug/build/ui
} else {
    DESTDIR = OpenTuring/Support
    OBJECTS_DIR = release/build/obj
    MOC_DIR = release/build/moc
    RCC_DIR = release/build/rcc
    UI_DIR = release/build/ui
}

HEADERS = \
    ./TuringEditor/mainwindow.h \
    ./TuringEditor/turinglexer.h \
    ./TuringEditor/findreplacedialog.h \
    TuringEditor/turingeditorwidget.h \
    TuringEditor/aboutbox.h \
    TuringEditor/turingrunner.h \
    TuringEditor/settingsdialog.h \
    TuringEditor/documentmanager.h \
    TuringEditor/signalmultiplexer.h \
    TuringEditor/osinterop.h \
    TuringEditor/resources/resource.h \
    TuringEditor/messagemanager.h \
    TuringEditor/docsview.h

SOURCES = \
    ./TuringEditor/turinglexer.cpp \
    ./TuringEditor/findreplacedialog.cpp \
    ./TuringEditor/mainwindow.cpp \
    TuringEditor/turingeditorwidget.cpp \
    TuringEditor/aboutbox.cpp \
    TuringEditor/turingrunner.cpp \
    TuringEditor/settingsdialog.cpp \
    TuringEditor/documentmanager.cpp \
    TuringEditor/signalmultiplexer.cpp \
    TuringEditor/osinterop.cpp \
    TuringEditor/messagemanager.cpp \
    TuringEditor/docsview.cpp

FORMS += \
	./TuringEditor/findreplacedialog.ui \
    TuringEditor/aboutbox.ui \
    TuringEditor/settingsdialog.ui

CONFIG(test_editor) {
    CONFIG += qtestlib
    HEADERS += test/testeditor.h
    SOURCES += test/testeditor.cpp
} else {
    SOURCES += TuringEditor/main.cpp
}

# include the library that allows single instance checking
include(qtsingleapplication/src/qtsingleapplication.pri)
# include the json parser library
# include(QJson/json.pri)


