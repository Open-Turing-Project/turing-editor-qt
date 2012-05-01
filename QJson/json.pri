
equals(QT_MAJOR_VERSION, 4): greaterThan(QT_MINOR_VERSION, 6) {
     QT+=network
} else {
     MOBILITY+=bearer
}

symbian:TARGET.CAPABILITY += NetworkServices

QT += declarative

INCLUDEPATH += ./QJson
DEPENDPATH  += ./QJson

HEADERS += \
    json_parser.hh \
    json_scanner.h \
    location.hh \
    qjson.h \
    qjson_p.h \
    parserrunnable.h \
    position.hh \
    qjson_debug.h \    
    qobjecthelper.h \
    serializer.h \
    serializerrunnable.h \
    stack.hh


SOURCES += \
    json_parser.cc \
    json_scanner.cpp \
    qjson.cpp \
    parserrunnable.cpp \
    qobjecthelper.cpp \
    serializer.cpp \
    serializerrunnable.cpp

OTHER_FILES += json_parser.yy
