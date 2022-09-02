#pragma once

#include <string>
#include "utilsmath.h"

namespace Leon::Utils {
	template<class T>
	std::string itos(const T& t)
	{
		char* a = itoc<T>(t);
		std::string ret(a);
		delete[] a;
		return ret;
	}

	template<class T>
	char* itoc(T t)
	{
		uint8 size;
		uint8 i;
		char* ret;
		if (t < 0) {
			t *= -1;
			size = log10whole(t) + 1;
			ret = new char[size + 1];
			ret[0] = '-';
			ret[size] = '\0';
			i = size;
			size = 1;
		}
		else {
			size = log10whole(t);
			ret = new char[size + 1];
			ret[size] = '\0';
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