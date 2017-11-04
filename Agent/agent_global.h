#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(AGENT_LIB)
#  define AGENT_EXPORT Q_DECL_EXPORT
# else
#  define AGENT_EXPORT Q_DECL_IMPORT
# endif
#else
# define AGENT_EXPORT
#endif
