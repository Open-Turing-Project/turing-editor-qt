// This module implements the TuringLexer class.
//
// Copyright (c) 2011 Riverbank Computing Limited <info@riverbankcomputing.com>
//
// This file is part of QScintilla.
//
// This file may be used under the terms of the GNU General Public
// License versions 2.0 or 3.0 as published by the Free Software
// Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
// included in the packaging of this file.  Alternatively you may (at
// your option) use any later version of the GNU General Public
// License if such license has been publicly approved by Riverbank
// Computing Limited (or its successors, if any) and the KDE Free Qt
// Foundation. In addition, as a special exception, Riverbank gives you
// certain additional rights. These rights are described in the Riverbank
// GPL Exception version 1.1, which can be found in the file
// GPL_EXCEPTION.txt in this package.
//
// Please review the following information to ensure GNU General
// Public Licensing requirements will be met:
// http://trolltech.com/products/qt/licenses/licensing/opensource/. If
// you are unsure which license is appropriate for your use, please
// review the following information:
// http://trolltech.com/products/qt/licenses/licensing/licensingoverview
// or contact the sales department at sales@riverbankcomputing.com.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#include "turinglexer.h"

#include <qcolor.h>
#include <qfont.h>
#include <qsettings.h>
#include "Qsci/qsciapis.h"
#include <QDebug>


// The ctor.
TuringLexer::TuringLexer(QObject *parent)
    : QsciLexer(parent),
      fold_compact(true)
{
    QsciAPIs* turingFuncs = new QsciAPIs(this);
    connect(turingFuncs,SIGNAL(apiPreparationFinished()),this,SLOT(apiPreparationFinished()));
    //connect(turingFuncs,SIGNAL(apiPreparationStarted()),this,SLOT(apiPreparationFinished()));

    bool loaded = turingFuncs->load(":/resources/APIs.txt");
    if(loaded){
        turingFuncs->prepare();
    } else{
        printf("can not load APIs!\n");
    }
    setAPIs(turingFuncs);

    loadSettings();

    theme = "Default";
}

// The dtor.
TuringLexer::~TuringLexer()
{
}

void TuringLexer::loadSettings()
{
    QSettings settings;
    fontSize = settings.value("fontSize",10).toInt();
    stringEOLHighlight = settings.value("stringEOLHighlight",false).toBool();
    fontFamily = settings.value("editorFont","Courier New").toString();
}

void TuringLexer::apiPreparationFinished() {
    printf("API preparation finished\n");
}

// Returns the language name.
const char *TuringLexer::language() const
{
    return "Turing";
}


// Returns the lexer name.
const char *TuringLexer::lexer() const
{
    return "turing";
}

void TuringLexer::setTheme(QString t) {
    theme = t;
    setDefaultPaper(defaultPaper(0));
    //colors updated
    for(int i = 20;i>=0;i--){
        emit colorChanged(defaultColor(i),i);
    }
    for(int i = 19;i>=0;i--){
        emit paperChanged(defaultPaper(i),i);
    }
    for(int i = 19;i>=0;i--){
        emit fontChanged(defaultFont(i),i);
    }
}

QString TuringLexer::getTheme() {
    return theme;
}


// Return the set of character sequences that can separate auto-completion
// words.
QStringList TuringLexer::autoCompletionWordSeparators() const
{
    QStringList wl;

    wl << "." << "->";

    return wl;
}


// Return the list of characters that can start a block.
const char *TuringLexer::blockStart(int *style) const
{
    if (style)
        *style = Operator;

    return "";
}


// Return the style used for braces.
int TuringLexer::braceStyle() const
{
    return Operator;
}


// Returns the foreground colour of the text for a style.
QColor TuringLexer::lightDefaultColor(int style) const
{
    switch (style)
    {
    case Default:
        return QColor(0x00,0x00,0x00);

    case Comment:
    case LineComment:
        return QColor(0x00,0x7f,0x00);

    case Keyword:
    case BasicFunctions:
    case StringTableMathsFunctions:
    case CoroutinesIOSystemFacilities:
        return QColor(0x00,0x00,0x00);

    case String:
    case Character:
    case LiteralString:
    case UnclosedString:
        return QColor(0x7f,0x00,0x00);

    case Preprocessor:
        return QColor(0x00,0x00,0x00);

    case Identifier:
        return QColor(0x00,0x00,0xff);
    case Number:
    case Operator:
        break;
    }

    return QsciLexer::defaultColor(style);
}

// Returns the foreground colour of the text for a style.
QColor TuringLexer::darkDefaultColor(int style) const
{
    switch (style)
    {
    case Operator:
    case Default:
        return QColor(0xff,0xff,0xff);

    case Comment:
    case LineComment:
        return QColor(95,90,96);

    case Keyword:
    case BasicFunctions:
    case StringTableMathsFunctions:
    case CoroutinesIOSystemFacilities:
        return QColor(205,168,105);

    case String:
    case Character:
    case LiteralString:
    case UnclosedString:
        return QColor(143,157,106);

    case Preprocessor:
        return QColor(0x00,0x00,0x00);


    case Identifier:
        return QColor(0xff,0xff,0xff);
    case Number:
        return QColor(207,106,76);
    }

    return QsciLexer::defaultColor(style);
}

// Returns the foreground colour of the text for a style.
QColor TuringLexer::defaultColor(int style) const
{
    if(theme == "Dark"){
        return darkDefaultColor(style);
    } else {
        return lightDefaultColor(style);
    }
}


// Returns the end-of-line fill for a style.
bool TuringLexer::defaultEolFill(int style) const
{
    if ((style == Comment || style == UnclosedString) && stringEOLHighlight)
        return true;

    return QsciLexer::defaultEolFill(style);
}


// Returns the font of the text for a style.
QFont TuringLexer::defaultFont(int style) const
{
    QFont f(fontFamily,fontSize);
    if(theme == "Dark"){
        switch (style)
        {
        case Comment:
        case LineComment:
            f.setItalic(true);
        }
    } else {
        switch (style)
        {
        case Keyword:
            f.setBold(true);
        }
    }
    return f;
}


// Returns the set of keywords.
const char *TuringLexer::keywords(int set) const
{
    if (set == 1)
        // Keywords.
        return
            "addressint all and array asm "
						"assert begin bind bits body "
						"boolean break by case char "
						"cheat checked class close collection "
						"condition const decreasing def deferred "
						"div else elseif elsif end "
						"enum exit "
						"export external false fcn flexible "
						"for fork forward free function "
						"get handler if implement import "
						"in include inherit init int "
						"int1 int2 int4 invariant label "
						"loop mod module monitor nat "
						"nat1 nat2 nat4 new not "
						"objectclass of opaque open or "
						"packed pause pervasive pointer post "
						"pre priority proc procedure process "
						"put quit read real real4 "
						"real8 record register rem result "
						"return seek self set shl "
						"shr signal skip string tag "
						"tell then timeout to true "
						"type unchecked union unqualified var "
						"wait when write xor";

    if (set == 2)
        // Basic functions.
        return
            "Draw Mouse View";

    if (set == 3)
        // String, table and maths functions.
        return
            "drawdot drawline";

    if (set == 4)
        // Coroutine, I/O and system facilities.
        return
            "Parallel process";

    return 0;
}


// Returns the user name of a style.
QString TuringLexer::description(int style) const
{
    switch (style)
    {
    case Default:
        return tr("Default");

    case Comment:
        return tr("Comment");

    case LineComment:
        return tr("Line comment");

    case Number:
        return tr("Number");

    case Keyword:
        return tr("Keyword");

    case String:
        return tr("String");

    case Character:
        return tr("Character");

    case LiteralString:
        return tr("Literal string");

    case Preprocessor:
        return tr("Preprocessor");

    case Operator:
        return tr("Operator");

    case Identifier:
        return tr("Identifier");

    case UnclosedString:
        return tr("Unclosed string");

    case BasicFunctions:
        return tr("Basic functions");

    case StringTableMathsFunctions:
        return tr("String, table and maths functions");

    case CoroutinesIOSystemFacilities:
        return tr("Coroutines, i/o and system facilities");

    case KeywordSet5:
        return tr("User defined 1");

    case KeywordSet6:
        return tr("User defined 2");

    case KeywordSet7:
        return tr("User defined 3");

    case KeywordSet8:
        return tr("User defined 4");
    }

    return QString();
}


// Returns the background colour of the text for a style.
QColor TuringLexer::defaultPaper(int style) const
{
    if(theme == "Dark"){
        switch (style)
        {
        case UnclosedString:
            if (stringEOLHighlight)
                return QColor(0x4f,0x14,0x14);
        }
        return QColor(0x14,0x14,0x14);
    } else {
        switch (style)
        {
        case UnclosedString:
            if (stringEOLHighlight)
                return QColor(0xe0,0xc0,0xc0);
        }
        return QColor(0xff,0xff,0xff);
    }
}


// Refresh all properties.
void TuringLexer::refreshProperties()
{
    setCompactProp();
}


// Read properties from the settings.
bool TuringLexer::readProperties(QSettings &qs,const QString &prefix)
{
    int rc = true;

    fold_compact = qs.value(prefix + "foldcompact", true).toBool();

    return rc;
}


// Write properties to the settings.
bool TuringLexer::writeProperties(QSettings &qs,const QString &prefix) const
{
    int rc = true;

    qs.setValue(prefix + "foldcompact", fold_compact);

    return rc;
}


// Return true if folds are compact.
bool TuringLexer::foldCompact() const
{
    return fold_compact;
}


// Set if folds are compact.
void TuringLexer::setFoldCompact(bool fold)
{
    fold_compact = fold;

    setCompactProp();
}


// Set the "fold.compact" property.
void TuringLexer::setCompactProp()
{
    emit propertyChanged("fold.compact",(fold_compact ? "1" : "0"));
}
