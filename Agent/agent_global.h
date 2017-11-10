#pragma once

#include <memory>
#include <cassert>
#include <QtCore/qglobal.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qobject.h>

#ifndef BUILD_STATIC
# if defined(AGENT_LIB)
#  define AGENT_EXPORT Q_DECL_EXPORT
# else
#  define AGENT_EXPORT Q_DECL_IMPORT
# endif
#else
# define AGENT_EXPORT
#endif
