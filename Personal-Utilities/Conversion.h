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
	constexpr bool isfloat(const std::string_view& inp)
	{
		int i = inp.size() > 0 ? (inp[0] == '-' ? 1 : 0) : 0;
		bool sep = false;
		while (i < inp.size())
		{
			if (inp[i] == '.' || inp[i] == ',') {
				if (sep)
					return false;
				sep = true;
			}
			else if (!(inp[i] >= '0' && inp[i] <= '9')) {
				return false;
			}
		}
	}
	constexpr bool isdigit(const std::string_view& inp)
	{
		int i = inp.size() > 0 ? (inp[0] == '-' ? 1 : 0) : 0;
		while(i < inp.size()) {
			if (!(inp[i] >= '0' && inp[i] <= '9'))
				return false;
		}
		return true;
	}
}