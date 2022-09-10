#pragma once

#include "typedefs.h"
#include "Conversion.h"
namespace Reun::Utils
{
	template<typename Tomatch, typename... Ts>
	using MatchesType = std::enable_if_t<std::conjunction_v<std::is_same<Tomatch, Ts>... >> ;
}