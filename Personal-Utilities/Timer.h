#pragma once
#if 0
namespace Leon::Utils
{
	class Timer
	{
	public:
		Timer() {};
		//~Timer() {};
		void Start() {};
		float Stopms() { return 0.0f; }
		float Stopmic() { return 0.0f; }
	};
}
#else

#include <stdint.h>
#include <chrono>


namespace Reun::Utils {
	class Timer
	{
	public:
		Timer() : duration(0) {}
		//~Timer() {}
		void Start() {
			start = std::chrono::high_resolution_clock::now();
		}
		float Stopms() {
			end = std::chrono::high_resolution_clock::now();
			duration = (end - start);
			return static_cast<float>(duration.count()) * static_cast<float>(1e-6);
		}
		float Stopmic() {
			end = std::chrono::high_resolution_clock::now();
			duration = (end - start);
			return static_cast<float>(duration.count()) * static_cast<float>(1e-3);
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::nanoseconds duration;
	};
}
#endif