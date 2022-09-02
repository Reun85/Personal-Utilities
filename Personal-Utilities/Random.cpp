#include "LNpch.h"
#include "Random.h"

void Leon::Utils::MoveObjectTo(char* dest, char* src)
{
	memcpy(dest, src, strlen(src));
	delete[] src;
}

void Leon::Utils::placenumberin(char* output, uint32 inp)
{
	MoveObjectTo(output, itoc(inp));
}

void Leon::Utils::placenumberincheckformissingzero(char* output, uint32 inp)
{
	if (inp < 10) {
		placenumberin(output + 1, std::forward<uint32>(inp));
		*output = '0';
	}
	else
	{
		placenumberin(output, std::forward<uint32>(inp));
	}
}
