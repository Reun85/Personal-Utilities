#pragma once
#include "typedefs.h"
#include "Random.h"
#include <chrono>
#include <string>
namespace Reun::Utils::Date {


	std::string GetCurrentDate(const std::string_view& separator1 = "-", const bool firsttwoinyear = false);

	std::string GetCurrentDate(const bool firsttwoinyear);
	std::string GetCurrentDateHourMin(const std::string_view& separator1 = "-", const std::string_view& separator2 = " ", const std::string_view& separator3 = "-", const bool firsttwoinyear = false);
	std::string GetCurrentDateHourMin(const bool firsttwoinyear);
	namespace Inner
	{

	}
}

namespace Reun::Utils
{
	using namespace Date;
}