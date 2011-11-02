// The implementation of various Qt version independent classes used by the
// rest of the port.
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


#include "SciClasses.h"

#include <qevent.h>
#include <qpainter.h>

#include "ScintillaQt.h"
#include "ListBoxQt.h"


// Create a call tip.
SciCallTip::SciCallTip(QWidget *parent, ScintillaQt *sci_)
    : QWidget(parent, 0, Qt::WType_Popup|Qt::WStyle_Customize|Qt::WStyle_NoBorder),
      sci(sci_)
{
    // Ensure that the main window keeps the focus (and the caret flashing)
    // when this is displayed.
    setFocusProxy(parent);
}


// Destroy a call tip.
SciCallTip::~SciCallTip()
{
    // Ensure that the main window doesn't receive a focus out event when
    // this is destroyed.
    setFocusProxy(0);
}


// Paint a call tip.
void SciCallTip::paintEvent(QPaintEvent *)
{
    Surface *surfaceWindow = Surface::Allocate();

    if (!surfaceWindow)
        return;

    QPainter p(this);

    surfaceWindow->Init(&p);
    sci->ct.PaintCT(surfaceWindow);

    delete surfaceWindow;
}


// Handle a mouse press in a call tip.
void SciCallTip::mousePressEvent(QMouseEvent *e)
{
    Point pt;

    pt.x = e->x();
    pt.y = e->y();

    sci->ct.MouseClick(pt);
    sci->CallTipClick();

    update();
}



// Add an item and associated command to the popup and enable it if required.
void SciPopup::addItem(const QString &label, int cmd, bool enabled,
        ScintillaQt *sci_)
{
    insertItem(label, this, SLOT(on_triggered(int)), 0, cmd);
    setItemEnabled(cmd, enabled);
    sci = sci_;
}


// Add a separator to the popup.
void SciPopup::addSeparator()
{
    insertSeparator();
}


// A slot to handle a menu action being triggered.
void SciPopup::on_triggered(int cmd)
{
    sci->Command(cmd);
}



SciListBox::SciListBox(QWidget *parent, ListBoxQt *lbx_)
    : QListBox(parent,0,Qt::WType_Popup|Qt::WStyle_Customize|Qt::WStyle_NoBorder|Qt::WStaticContents), lbx(lbx_)
{
    setFocusProxy(parent);

    setFrameShape(StyledPanel);
    setFrameShadow(Plain);

    connect(this,SIGNAL(doubleClicked(QListBoxItem *)),
        SLOT(handleSelection()));

    connect(this,SIGNAL(highlighted(QListBoxItem *)),
        SLOT(ensureCurrentVisible()));
}


int SciListBox::find(const QString &prefix)
{
    return index(findItem(prefix, Qt::CaseSensitive|Qt::BeginsWith));
}



SciListBox::~SciListBox()
{
    // Ensure that the main widget doesn't get a focus out event when this is
    // destroyed.
    setFocusProxy(0);
}


void SciListBox::handleSelection()
{
    if (lbx && lbx->cb_action)
        lbx->cb_action(lbx->cb_data);
}
