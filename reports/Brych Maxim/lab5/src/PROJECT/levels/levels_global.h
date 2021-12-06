#ifndef LEVELS_GLOBAL_H
#define LEVELS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LEVELS_LIBRARY)
#  define LEVELS_EXPORT Q_DECL_EXPORT
#else
#  define LEVELS_EXPORT Q_DECL_IMPORT
#endif

#endif // LEVELS_GLOBAL_H
