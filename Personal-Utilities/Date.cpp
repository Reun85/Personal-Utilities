#include "LNpch.h"
#include "Date.h"

void Leon::Utils::GetCurrentDateHourMin(char* output)
{
	using namespace std;
	using namespace std::chrono;
	using namespace Leon::Utils;

	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm;
	localtime_s(&local_tm, &tt);
	output[19] = '\0';
	output[4] = '-';
	output[7] = '-';
	output[10] = ' ';
	output[13] = '-';
	output[16] = '-';
	placenumberin(&output[0], local_tm.tm_year + 1900);
	placenumberincheckformissingzero(&output[5], local_tm.tm_mon + 1);
	placenumberincheckformissingzero(&output[8], local_tm.tm_mday);
	placenumberincheckformissingzero(&output[11], local_tm.tm_hour);
	placenumberincheckformissingzero(&output[14], local_tm.tm_min);
	placenumberincheckformissingzero(&output[17], local_tm.tm_sec);
}

const char* Leon::Utils::GetCurrentDateHourMin()
{
	char* ret = new char[20];
	GetCurrentDateHourMin(ret);
	return ret;
}
