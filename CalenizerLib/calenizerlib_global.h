#ifndef CALENIZERLIB_GLOBAL_H
#define CALENIZERLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CALENIZERLIB_LIB
# define CALENIZERLIB_EXPORT Q_DECL_EXPORT
#else
# define CALENIZERLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // CALENIZERLIB_GLOBAL_H
