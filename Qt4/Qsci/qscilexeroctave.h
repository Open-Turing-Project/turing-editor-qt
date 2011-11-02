// This defines the interface to the QsciLexerOctave class.
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


#ifndef QSCILEXEROCTAVE_H
#define QSCILEXEROCTAVE_H

#ifdef __APPLE__
extern "C++" {
#endif

#include <qobject.h>

#include <Qsci/qsciglobal.h>
#include <Qsci/qscilexermatlab.h>


//! \brief The QsciLexerOctave class encapsulates the Scintilla Octave file
//! lexer.
class QSCINTILLA_EXPORT QsciLexerOctave : public QsciLexerMatlab
{
    Q_OBJECT

public:
    //! Construct a QsciLexerOctave with parent \a parent.  \a parent is
    //! typically the QsciScintilla instance.
    QsciLexerOctave(QObject *parent = 0);

    //! Destroys the QsciLexerOctave instance.
    virtual ~QsciLexerOctave();

    //! Returns the name of the language.
    const char *language() const;

    //! Returns the name of the lexer.  Some lexers support a number of
    //! languages.
    const char *lexer() const;

    //! Returns the set of keywords for the keyword set \a set recognised
    //! by the lexer as a space separated string.
    const char *keywords(int set) const;

private:
    QsciLexerOctave(const QsciLexerOctave &);
    QsciLexerOctave &operator=(const QsciLexerOctave &);
};

#ifdef __APPLE__
}
#endif

#endif
