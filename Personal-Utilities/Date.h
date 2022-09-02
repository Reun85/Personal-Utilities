#pragma once
#include "typedefs.h"
#include "Random.h"
#include <chrono>

namespace Leon::Utils {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="output">Minimum length of 20, sets the 20th element to '\0' </param>
	void GetCurrentDateHourMin(char* output);
	/// <summary>
	/// Returns a null terminated cstr of the current date
	/// </summary>
	/// <returns></returns>
	const char* GetCurrentDateHourMin();
}