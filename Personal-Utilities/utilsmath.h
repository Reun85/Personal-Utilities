#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "typedefs.h"


namespace Reun::Utils {
	inline void InitRand() {
		srand((uint8)time(NULL));
	}
	template<typename T>
	constexpr inline T clamp(const T& value, const T& min, const T& max)
	{
		return std::max(min, std::min(value, max));
	}
	template<typename T>
	constexpr T map(const T value, const T beforemin, const T beforemax, const T aftermin, const T aftermax)
	{
		return (((value-beforemin) / (beforemax-beforemin))* (aftermax-aftermin))+aftermin;
	}
	template<class T>
	uint8 log10whole(T t)
	{
		uint8 ret = 0;
		do
		{
			ret++;
			t /= 10;
		} while (t > 0);
		return ret;
	}
	constexpr uint64 mypow(const uint64& base, const uint64& exponent)
	{
		uint64 ret = 1;
		for (uint8 i = 0; i < exponent; i++)
		{
			ret *= base;
		}
		return ret;
	}
}