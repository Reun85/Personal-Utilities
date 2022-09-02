#pragma once

#include "typedefs.h"

namespace Leon::Utils {
	template<class T>
	constexpr uint8 getsizeof()
	{
		return sizeof(T);
	}
	template<>
	constexpr uint8 getsizeof<uint8>()
	{
		return 1;
	}
	template<>
	constexpr uint8 getsizeof<int8>()
	{
		return 1;
	}
	template<>
	constexpr uint8 getsizeof<uint16>()
	{
		return 2;
	}
	template<>
	constexpr uint8 getsizeof<int16>()
	{
		return 2;
	}
	template<>
	constexpr uint8 getsizeof<uint32>()
	{
		return 4;
	}
	template<>
	constexpr uint8 getsizeof<int32>()
	{
		return 4;
	}

	template<>
	constexpr uint8 getsizeof<uint64>()
	{
		return 8;
	}

	template<>
	constexpr uint8 getsizeof<int64>()
	{
		return 8;
	}

	template<class T>
	constexpr inline void* memorycopy(T* dst, T* src, size_t size)
	{
		return memcpy(dst, src, size * getsizeof<T>());
	}
}