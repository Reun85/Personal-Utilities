#include "Date.h"

namespace Reun::Utils {
	std::string GetCurrentDate(const bool firsttwoinyear);
	{
		return move(GetCurrentDate("-", firsttwoinyear));
	}
	std::string GetCurrentDate(const std::string_view& separator1, const bool firsttwoinyear);
	{
		using namespace std;
		using namespace std::chrono;
		using namespace Inner;
		time_t tt = system_clock::to_time_t(system_clock::now());
		tm local_tm;
		localtime_s(&local_tm, &tt);

		std::string ret;
		ret.resize()
		return move(ret);
	}
}