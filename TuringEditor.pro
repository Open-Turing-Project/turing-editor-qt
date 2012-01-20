# The project file for the QScintilla library.
#
# Copyright (c) 2011 Riverbank Computing Limited <info@riverbankcomputing.com>
# 
# This file is part of QScintilla.
# 
# This file may be used under the terms of the GNU General Public
# License versions 2.0 or 3.0 as published by the Free Software
# Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
# included in the packaging of this file.  Alternatively you may (at
# your option) use any later version of the GNU General Public
# License if such license has been publicly approved by Riverbank
# Computing Limited (or its successors, if any) and the KDE Free Qt
# Foundation. In addition, as a special exception, Riverbank gives you
# certain additional rights. These rights are described in the Riverbank
# GPL Exception version 1.1, which can be found in the file
# GPL_EXCEPTION.txt in this package.
# 
# Please review the following information to ensure GNU General
# Public Licensing requirements will be met:
# http://trolltech.com/products/qt/licenses/licensing/opensource/. If
# you are unsure which license is appropriate for your use, please
# review the following information:
# http://trolltech.com/products/qt/licenses/licensing/licensingoverview
# or contact the sales department at sales@riverbankcomputing.com.
# 
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

# Open Turing Version

CURRENT_VERSION = 1.1.0 alpha
VERSTR = '\\"$${CURRENT_VERSION}\\"'  # place quotes around the version string
DEFINES = VERSION_STRING=\"$${VERSTR}\" # create a VER macro containing the version string

# files used in the running process
# usually the turing editor and turing prolog
# TURING_COMPILER is passed -compile <file.t>
# TURING_RUNNER is passed -file <file.tbc>
release {
    TURING_COMPILER = ../turing.exe
    TURING_RUNNER = ../support/bin/TuringEXEProlog.exe
} else {
    TURING_COMPILER = OldEditor.exe
    TURING_RUNNER = support/bin/TuringEXEProlog.exe
}

HELP_FILE = ../support/help/TuringDoc.chm

HELP_FILE_STR = '\\"$${HELP_FILE}\\"'
DEFINES += HELP_FILE_PATH=\"$${HELP_FILE_STR}\"

TURING_COMPILER_STR = '\\"$${TURING_COMPILER}\\"'
DEFINES += COMPILER_PATH=\"$${TURING_COMPILER_STR}\"

TURING_RUNNER_STR = '\\"$${TURING_RUNNER}\\"'
DEFINES += RUNNER_PATH=\"$${TURING_RUNNER_STR}\"

# QScintilla Version
# This must be kept in sync with configure.py.
!win32:VERSION = 6.1.0

#TEMPLATE = lib
TARGET = OpenTuring
CONFIG += qt thread
release {
    CONFIG += warn_off
} else {
    CONFIG += debug
}

INCLUDEPATH = ./QScintilla/Qt4 ./QScintilla/include ./QScintilla/lexlib ./QScintilla/src \
             ./TuringEditor ./TuringEditor/resources
RESOURCES = ./TuringEditor/turing.qrc
DEFINES += QT SCI_LEXER

RC_FILE = TuringEditor/resources/turing.rc

CONFIG(test_editor) {
    DESTDIR = test/build
    OBJECTS_DIR = test/build/obj
    MOC_DIR = test/build/moc
    RCC_DIR = test/build/rcc
    UI_DIR = test/build/ui
} else:debug {
    DESTDIR = debug
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
} else {
    DESTDIR = release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
}



# Handle both Qt v4 and v3.
target.path = $$[QT_INSTALL_LIBS]
isEmpty(target.path) {
	target.path = $(QTDIR)/lib
}

header.path = $$[QT_INSTALL_HEADERS]
header.files = Qsci
isEmpty(header.path) {
	header.path = $(QTDIR)/include/Qsci
	header.files = ./QScintilla/Qt4/Qsci/qsci*.h
}

trans.path = $$[QT_INSTALL_TRANSLATIONS]
trans.files = qscintilla_*.qm
isEmpty(trans.path) {
	trans.path = $(QTDIR)/translations
}

qsci.path = $$[QT_INSTALL_DATA]
qsci.files = ./QScintilla/qsci
isEmpty(qsci.path) {
	qsci.path = $(QTDIR)
}

INSTALLS += header trans qsci target

HEADERS = \
	./TuringEditor/mainwindow.h \
	./TuringEditor/turinglexer.h \
	./TuringEditor/findreplacedialog.h \
	./QScintilla/Qt4/Qsci/qsciglobal.h \
	./QScintilla/Qt4/Qsci/qsciscintilla.h \
	./QScintilla/Qt4/Qsci/qsciscintillabase.h \
	./QScintilla/Qt4/Qsci/qsciabstractapis.h \
	./QScintilla/Qt4/Qsci/qsciapis.h \
	./QScintilla/Qt4/Qsci/qscicommand.h \
	./QScintilla/Qt4/Qsci/qscicommandset.h \
	./QScintilla/Qt4/Qsci/qscidocument.h \
	./QScintilla/Qt4/Qsci/qscilexer.h \
	./QScintilla/Qt4/Qsci/qscilexerbash.h \
	./QScintilla/Qt4/Qsci/qscilexerbatch.h \
	./QScintilla/Qt4/Qsci/qscilexercmake.h \
	./QScintilla/Qt4/Qsci/qscilexercpp.h \
	./QScintilla/Qt4/Qsci/qscilexercsharp.h \
	./QScintilla/Qt4/Qsci/qscilexercss.h \
	./QScintilla/Qt4/Qsci/qscilexercustom.h \
	./QScintilla/Qt4/Qsci/qscilexerd.h \
	./QScintilla/Qt4/Qsci/qscilexerdiff.h \
	./QScintilla/Qt4/Qsci/qscilexerfortran.h \
	./QScintilla/Qt4/Qsci/qscilexerfortran77.h \
	./QScintilla/Qt4/Qsci/qscilexerhtml.h \
	./QScintilla/Qt4/Qsci/qscilexeridl.h \
	./QScintilla/Qt4/Qsci/qscilexerjava.h \
	./QScintilla/Qt4/Qsci/qscilexerjavascript.h \
	./QScintilla/Qt4/Qsci/qscilexerlua.h \
	./QScintilla/Qt4/Qsci/qscilexermakefile.h \
	./QScintilla/Qt4/Qsci/qscilexermatlab.h \
	./QScintilla/Qt4/Qsci/qscilexeroctave.h \
	./QScintilla/Qt4/Qsci/qscilexerpascal.h \
	./QScintilla/Qt4/Qsci/qscilexerperl.h \
	./QScintilla/Qt4/Qsci/qscilexerpostscript.h \
	./QScintilla/Qt4/Qsci/qscilexerpov.h \
	./QScintilla/Qt4/Qsci/qscilexerproperties.h \
	./QScintilla/Qt4/Qsci/qscilexerpython.h \
	./QScintilla/Qt4/Qsci/qscilexerruby.h \
	./QScintilla/Qt4/Qsci/qscilexerspice.h \
	./QScintilla/Qt4/Qsci/qscilexersql.h \
	./QScintilla/Qt4/Qsci/qscilexertcl.h \
	./QScintilla/Qt4/Qsci/qscilexertex.h \
	./QScintilla/Qt4/Qsci/qscilexerverilog.h \
	./QScintilla/Qt4/Qsci/qscilexervhdl.h \
	./QScintilla/Qt4/Qsci/qscilexerxml.h \
	./QScintilla/Qt4/Qsci/qscilexeryaml.h \
	./QScintilla/Qt4/Qsci/qscimacro.h \
	./QScintilla/Qt4/Qsci/qsciprinter.h \
	./QScintilla/Qt4/Qsci/qscistyle.h \
	./QScintilla/Qt4/Qsci/qscistyledtext.h \
	./QScintilla/Qt4/ListBoxQt.h \
	./QScintilla/Qt4/SciClasses.h \
	./QScintilla/Qt4/ScintillaQt.h \
	./QScintilla/include/ILexer.h \
	./QScintilla/include/Platform.h \
	./QScintilla/include/SciLexer.h \
	./QScintilla/include/Scintilla.h \
	./QScintilla/include/ScintillaWidget.h \
	./QScintilla/lexlib/Accessor.h \
	./QScintilla/lexlib/CharacterSet.h \
	./QScintilla/lexlib/LexAccessor.h \
	./QScintilla/lexlib/LexerBase.h \
	./QScintilla/lexlib/LexerModule.h \
	./QScintilla/lexlib/LexerNoExceptions.h \
	./QScintilla/lexlib/LexerSimple.h \
	./QScintilla/lexlib/OptionSet.h \
	./QScintilla/lexlib/PropSetSimple.h \
	./QScintilla/lexlib/StyleContext.h \
	./QScintilla/lexlib/WordList.h \
	./QScintilla/src/AutoComplete.h \
	./QScintilla/src/CallTip.h \
	./QScintilla/src/Catalogue.h \
	./QScintilla/src/CellBuffer.h \
	./QScintilla/src/CharClassify.h \
	./QScintilla/src/ContractionState.h \
	./QScintilla/src/Decoration.h \
	./QScintilla/src/Document.h \
	./QScintilla/src/Editor.h \
	./QScintilla/src/ExternalLexer.h \
	./QScintilla/src/FontQuality.h \
	./QScintilla/src/Indicator.h \
	./QScintilla/src/KeyMap.h \
	./QScintilla/src/LineMarker.h \
	./QScintilla/src/Partitioning.h \
	./QScintilla/src/PerLine.h \
	./QScintilla/src/PositionCache.h \
	./QScintilla/src/RESearch.h \
	./QScintilla/src/RunStyles.h \
	./QScintilla/src/ScintillaBase.h \
	./QScintilla/src/Selection.h \
	./QScintilla/src/SplitVector.h \
	./QScintilla/src/Style.h \
	./QScintilla/src/SVector.h \
	./QScintilla/src/UniConversion.h \
	./QScintilla/src/ViewStyle.h \
	./QScintilla/src/XPM.h \
    TuringEditor/turingeditorwidget.h \
    TuringEditor/aboutbox.h \
    TuringEditor/turingrunner.h \
    TuringEditor/settingsdialog.h \
    TuringEditor/documentmanager.h \
    TuringEditor/signalmultiplexer.h \
    TuringEditor/osinterop.h \
    TuringEditor/resources/resource.h

SOURCES = \
	./TuringEditor/turinglexer.cpp \
	./TuringEditor/findreplacedialog.cpp \
	./TuringEditor/mainwindow.cpp \
	./QScintilla/Qt4/qsciscintilla.cpp \
	./QScintilla/Qt4/qsciscintillabase.cpp \
	./QScintilla/Qt4/qsciabstractapis.cpp \
	./QScintilla/Qt4/qsciapis.cpp \
	./QScintilla/Qt4/qscicommand.cpp \
	./QScintilla/Qt4/qscicommandset.cpp \
	./QScintilla/Qt4/qscidocument.cpp \
	./QScintilla/Qt4/qscilexer.cpp \
	./QScintilla/Qt4/qscilexerbash.cpp \
	./QScintilla/Qt4/qscilexerbatch.cpp \
	./QScintilla/Qt4/qscilexercmake.cpp \
	./QScintilla/Qt4/qscilexercpp.cpp \
	./QScintilla/Qt4/qscilexercsharp.cpp \
	./QScintilla/Qt4/qscilexercss.cpp \
	./QScintilla/Qt4/qscilexercustom.cpp \
	./QScintilla/Qt4/qscilexerd.cpp \
	./QScintilla/Qt4/qscilexerdiff.cpp \
	./QScintilla/Qt4/qscilexerfortran.cpp \
	./QScintilla/Qt4/qscilexerfortran77.cpp \
	./QScintilla/Qt4/qscilexerhtml.cpp \
	./QScintilla/Qt4/qscilexeridl.cpp \
	./QScintilla/Qt4/qscilexerjava.cpp \
	./QScintilla/Qt4/qscilexerjavascript.cpp \
	./QScintilla/Qt4/qscilexerlua.cpp \
	./QScintilla/Qt4/qscilexermakefile.cpp \
	./QScintilla/Qt4/qscilexermatlab.cpp \
	./QScintilla/Qt4/qscilexeroctave.cpp \
	./QScintilla/Qt4/qscilexerpascal.cpp \
	./QScintilla/Qt4/qscilexerperl.cpp \
	./QScintilla/Qt4/qscilexerpostscript.cpp \
	./QScintilla/Qt4/qscilexerpov.cpp \
	./QScintilla/Qt4/qscilexerproperties.cpp \
	./QScintilla/Qt4/qscilexerpython.cpp \
	./QScintilla/Qt4/qscilexerruby.cpp \
	./QScintilla/Qt4/qscilexerspice.cpp \
	./QScintilla/Qt4/qscilexersql.cpp \
	./QScintilla/Qt4/qscilexertcl.cpp \
	./QScintilla/Qt4/qscilexertex.cpp \
	./QScintilla/Qt4/qscilexerverilog.cpp \
	./QScintilla/Qt4/qscilexervhdl.cpp \
	./QScintilla/Qt4/qscilexerxml.cpp \
	./QScintilla/Qt4/qscilexeryaml.cpp \
	./QScintilla/Qt4/qscimacro.cpp \
	./QScintilla/Qt4/qsciprinter.cpp \
	./QScintilla/Qt4/qscistyle.cpp \
	./QScintilla/Qt4/qscistyledtext.cpp \
	./QScintilla/Qt4/SciClasses.cpp \
	./QScintilla/Qt4/ListBoxQt.cpp \
	./QScintilla/Qt4/PlatQt.cpp \
	./QScintilla/Qt4/ScintillaQt.cpp \
	./QScintilla/lexers/LexA68k.cpp \
	./QScintilla/lexers/LexAbaqus.cpp \
	./QScintilla/lexers/LexAda.cpp \
	./QScintilla/lexers/LexAPDL.cpp \
	./QScintilla/lexers/LexAsm.cpp \
	./QScintilla/lexers/LexAsn1.cpp \
	./QScintilla/lexers/LexASY.cpp \
	./QScintilla/lexers/LexAU3.cpp \
	./QScintilla/lexers/LexAVE.cpp \
	./QScintilla/lexers/LexBaan.cpp \
	./QScintilla/lexers/LexBash.cpp \
	./QScintilla/lexers/LexBasic.cpp \
	./QScintilla/lexers/LexBullant.cpp \
	./QScintilla/lexers/LexCaml.cpp \
	./QScintilla/lexers/LexCLW.cpp \
	./QScintilla/lexers/LexCmake.cpp \
	./QScintilla/lexers/LexCOBOL.cpp \
	./QScintilla/lexers/LexConf.cpp \
	./QScintilla/lexers/LexCPP.cpp \
	./QScintilla/lexers/LexCrontab.cpp \
	./QScintilla/lexers/LexCsound.cpp \
	./QScintilla/lexers/LexCSS.cpp \
	./QScintilla/lexers/LexD.cpp \
	./QScintilla/lexers/LexEiffel.cpp \
	./QScintilla/lexers/LexErlang.cpp \
	./QScintilla/lexers/LexEScript.cpp \
	./QScintilla/lexers/LexFlagship.cpp \
	./QScintilla/lexers/LexForth.cpp \
	./QScintilla/lexers/LexFortran.cpp \
	./QScintilla/lexers/LexGAP.cpp \
	./QScintilla/lexers/LexGui4Cli.cpp \
	./QScintilla/lexers/LexHaskell.cpp \
	./QScintilla/lexers/LexHTML.cpp \
	./QScintilla/lexers/LexInno.cpp \
	./QScintilla/lexers/LexKix.cpp \
	./QScintilla/lexers/LexLisp.cpp \
	./QScintilla/lexers/LexLout.cpp \
	./QScintilla/lexers/LexLua.cpp \
	./QScintilla/lexers/LexMagik.cpp \
	./QScintilla/lexers/LexMarkdown.cpp \
	./QScintilla/lexers/LexMatlab.cpp \
	./QScintilla/lexers/LexMetapost.cpp \
	./QScintilla/lexers/LexMMIXAL.cpp \
	./QScintilla/lexers/LexModula.cpp \
	./QScintilla/lexers/LexMPT.cpp \
	./QScintilla/lexers/LexMSSQL.cpp \
	./QScintilla/lexers/LexMySQL.cpp \
	./QScintilla/lexers/LexNimrod.cpp \
	./QScintilla/lexers/LexNsis.cpp \
	./QScintilla/lexers/LexOpal.cpp \
	./QScintilla/lexers/LexOthers.cpp \
	./QScintilla/lexers/LexPascal.cpp \
	./QScintilla/lexers/LexPB.cpp \
	./QScintilla/lexers/LexPerl.cpp \
	./QScintilla/lexers/LexPLM.cpp \
	./QScintilla/lexers/LexPOV.cpp \
	./QScintilla/lexers/LexPowerPro.cpp \
	./QScintilla/lexers/LexPowerShell.cpp \
	./QScintilla/lexers/LexProgress.cpp \
	./QScintilla/lexers/LexPS.cpp \
	./QScintilla/lexers/LexPython.cpp \
	./QScintilla/lexers/LexR.cpp \
	./QScintilla/lexers/LexRebol.cpp \
	./QScintilla/lexers/LexRuby.cpp \
	./QScintilla/lexers/LexScriptol.cpp \
	./QScintilla/lexers/LexSmalltalk.cpp \
	./QScintilla/lexers/LexSML.cpp \
	./QScintilla/lexers/LexSorcus.cpp \
	./QScintilla/lexers/LexSpecman.cpp \
	./QScintilla/lexers/LexSpice.cpp \
	./QScintilla/lexers/LexSQL.cpp \
	./QScintilla/lexers/LexTACL.cpp \
	./QScintilla/lexers/LexTADS3.cpp \
	./QScintilla/lexers/LexTAL.cpp \
	./QScintilla/lexers/LexTCL.cpp \
	./QScintilla/lexers/LexTeX.cpp \
	./QScintilla/lexers/LexTuring.cpp \
	./QScintilla/lexers/LexTxt2tags.cpp \
	./QScintilla/lexers/LexVB.cpp \
	./QScintilla/lexers/LexVerilog.cpp \
	./QScintilla/lexers/LexVHDL.cpp \
	./QScintilla/lexers/LexYAML.cpp \
	./QScintilla/lexlib/Accessor.cpp \
	./QScintilla/lexlib/CharacterSet.cpp \
	./QScintilla/lexlib/LexerBase.cpp \
	./QScintilla/lexlib/LexerModule.cpp \
	./QScintilla/lexlib/LexerNoExceptions.cpp \
	./QScintilla/lexlib/LexerSimple.cpp \
	./QScintilla/lexlib/PropSetSimple.cpp \
	./QScintilla/lexlib/StyleContext.cpp \
	./QScintilla/lexlib/WordList.cpp \
	./QScintilla/src/AutoComplete.cpp \
	./QScintilla/src/CallTip.cpp \
	./QScintilla/src/Catalogue.cpp \
	./QScintilla/src/CellBuffer.cpp \
	./QScintilla/src/CharClassify.cpp \
	./QScintilla/src/ContractionState.cpp \
	./QScintilla/src/Decoration.cpp \
	./QScintilla/src/Document.cpp \
	./QScintilla/src/Editor.cpp \
	./QScintilla/src/ExternalLexer.cpp \
	./QScintilla/src/Indicator.cpp \
	./QScintilla/src/KeyMap.cpp \
	./QScintilla/src/LineMarker.cpp \
	./QScintilla/src/PerLine.cpp \
	./QScintilla/src/PositionCache.cpp \
	./QScintilla/src/RESearch.cpp \
	./QScintilla/src/RunStyles.cpp \
	./QScintilla/src/ScintillaBase.cpp \
	./QScintilla/src/Selection.cpp \
	./QScintilla/src/Style.cpp \
	./QScintilla/src/UniConversion.cpp \
	./QScintilla/src/ViewStyle.cpp \
	./QScintilla/src/XPM.cpp \
    TuringEditor/turingeditorwidget.cpp \
    TuringEditor/aboutbox.cpp \
    TuringEditor/turingrunner.cpp \
    TuringEditor/settingsdialog.cpp \
    TuringEditor/documentmanager.cpp \
    TuringEditor/signalmultiplexer.cpp \
    TuringEditor/osinterop.cpp

TRANSLATIONS = \
	./QScintilla/Qt4/qscintilla_cs.ts \
	./QScintilla/Qt4/qscintilla_de.ts \
	./QScintilla/Qt4/qscintilla_es.ts \
	./QScintilla/Qt4/qscintilla_fr.ts \
	./QScintilla/Qt4/qscintilla_pt_br.ts \
	./QScintilla/Qt4/qscintilla_ru.ts

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



















