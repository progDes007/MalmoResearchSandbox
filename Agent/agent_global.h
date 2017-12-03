#pragma once

#include <memory>
#include <cassert>
#include <QtCore/qglobal.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qobject.h>

#include <Mathematics\GteVector2.h>
#include <Mathematics\GteVector3.h>
#include <Mathematics\GteVector4.h>

using namespace gte;

typedef Vector2<double> Vector2d;
typedef Vector3<double> Vector3d;
typedef Vector4<double> Vector4d;

#ifndef BUILD_STATIC
# if defined(AGENT_LIB)
#  define AGENT_EXPORT Q_DECL_EXPORT
# else
#  define AGENT_EXPORT Q_DECL_IMPORT
# endif
#else
# define AGENT_EXPORT
#endif
