#ifndef HELPERCLASS_GLOBAL_HPP
#define HELPERCLASS_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(HELPERCLASS_LIBRARY)
#  define HELPERCLASS_EXPORT Q_DECL_EXPORT
#else
#  define HELPERCLASS_EXPORT Q_DECL_IMPORT
#endif

#endif // HELPERCLASS_GLOBAL_HPP
