CONFIG       += release
HEADERS       = mainwindow.h
SOURCES       = main.cpp \
                mainwindow.cpp
RESOURCES     = application.qrc
INCLUDEPATH += ../Qt4
macx {
QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@executable_path/../Frameworks/
}
unix:LIBS += -lqscintilla2 -L./application.app/Contents/Frameworks
