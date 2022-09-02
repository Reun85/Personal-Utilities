#pragma once

#include "Log/LogCore.h"

#if LN_USE_PROFILING == 1
#include "InstrumentationTimer.h"
#define LN_PROFILE_BEGIN_SESS(...) Leon::Utils::Instrumentor::Get().BeginSession(__VA_ARGS__);
#define LN_PROFILE_NAME(x) Leon::Utils::InstrumentationTimer timer##__FILE__##__LINE__(x);
#define LN_PROFILE() LN_PROFILE_NAME(__FUNCSIG__ )
#define LN_PROFILE_END_SESS() Leon::Utils::Instrumentor::Get().EndSession();

#else
#define LN_PROFILE_NAME(x)
#define LN_PROFILE()
#define LN_PROFILE_END_SESS()
#define LN_PROFILE_BEGIN_SESS(...)
#endif