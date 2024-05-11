#ifndef ZED_BASE_H
#define ZED_BASE_H

#include <assert.h>
#include "Zed/Core/Log.h"

#define BIT(x) (1 << x)

#ifdef ZED_ENABLE_ASSERTS
#define ZED_ASSERT(x, ...) { if(!(x)) { ZED_ERROR("Assertion Failed: {0}", __VA_ARGS__);assert(x); } }
#define ZED_CORE_ASSERT(x, ...) { if(!(x)) { ZED_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
#else
#define ZED_ASSERT(x, ...)
#define ZED_CORE_ASSERT(x, ...)
#endif

#endif //ZED_BASE_H