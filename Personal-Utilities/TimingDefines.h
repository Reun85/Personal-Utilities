#pragma once


#include <source_location>

#if UTILS_USE_PROFILING == 1
#include "InstrumentationTimer.h"
#define UTILS_PROFILE_BEGIN_SESS(...) Reun::Utils::Instrumentor::Get().BeginSession(__VA_ARGS__);
#define UTILS_PROFILE_NAME(x) Reun::Utils::InstrumentationTimer timer##__COUNTER__(x);
#define UTILS_PROFILE() UTILS_PROFILE_NAME(std::source_location::current())
#define UTILS_PROFILE_END_SESS() Reun::Utils::Instrumentor::Get().EndSession();

#else
#define UTILS_PROFILE_NAME(x)
#define UTILS_PROFILE()
#define UTILS_PROFILE_END_SESS()
#define UTILS_PROFILE_BEGIN_SESS(...)
#endif