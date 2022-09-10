#pragma once

#include <string>
#include "utilsmath.h"

namespace Reun::Utils {
	template<class T>
	std::string itos(const T& t)
	{
		uint8 size;
		uint8 i;
		std::string ret;
		ret.resize(size);
		if (t < 0) {
			t *= -1;
			size = log10whole(t) + 1;
			ret[0] = '-';
			i = size;
			size = 1;
		}
		else {
			size = log10whole(t);
			i = size;
			size = 0;
		}
		do
		{
			i--;
			ret[i] = (t % 10) + '0';
			t /= 10;
		} while (i != size);
		return ret;
	}
}