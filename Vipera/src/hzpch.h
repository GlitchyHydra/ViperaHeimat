#pragma once

#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <limits>

#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

#ifdef VIPERA_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

// The min/max macros conflict with like-named member functions.
// Only use std::min and std::max defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#if defined(CreateWindow)
#undef CreateWindow
#endif


#endif // VIPERA_PLATFORM_WINDOWS
