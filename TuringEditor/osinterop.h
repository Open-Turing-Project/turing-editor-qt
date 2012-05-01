#ifndef OSINTEROP_H
#define OSINTEROP_H

#include <QWidget>
#include <QString>
#include <QDir>

namespace OSInterop {
    QDir getExecutableDirectory();
    bool associateTuringFiles();
}

#endif // OSINTEROP_H
