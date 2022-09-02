#pragma once

#include "typedefs.h"
#include "Conversion.h"
namespace Leon::Utils
{
	template<typename Tomatch, typename... Ts>
	using MatchesType = std::enable_if_t<std::conjunction_v<std::is_same<Tomatch, Ts>... >> ;

	void MoveObjectTo(char* dest, char* src);
	
	template<typename T>
	void MoveObjectTo(T* dest, T* src, uint32 size)
	{
		memcpy(dest, src, size);
		delete[] src;
	}
	void placenumberin(char* output, uint32 inp);
	void placenumberincheckformissingzero(char* output, uint32 inp);
}