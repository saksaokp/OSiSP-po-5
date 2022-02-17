#ifndef FONT_GLOBAL_H
#define FONT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FONT_LIBRARY)
#  define FONT_EXPORT Q_DECL_EXPORT
#else
#  define FONT_EXPORT Q_DECL_IMPORT
#endif

#endif // FONT_GLOBAL_H
