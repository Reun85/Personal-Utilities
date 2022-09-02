#pragma once

#include "typedefs.h"

namespace Leon::Utils
{
	template<uint32 LengthofAverage, typename T> // typename T must support T a/N, and give an accurate result, eg: double, float
	class RollingAverage
	{
	public:
		RollingAverage();
		void Insertime(T);
		bool GetAvg(T& output);
	private:
		uint32 iterator;
		T m_rollingavg;
		T m_buff;
	};
	template<uint32 LengthofAverage, typename T>
	inline RollingAverage<LengthofAverage, T>::RollingAverage()
		: iterator(0), m_rollingavg(0), m_buff(0)
	{
	}
	template<uint32 LengthofAverage, typename T>
	inline void RollingAverage<LengthofAverage, T>::Insertime(T t)
	{
		m_rollingavg += t / static_cast<float>(LengthofAverage);
		iterator++;
		if (iterator == LengthofAverage) {
			iterator = 0;
			m_buff = m_rollingavg;
			m_rollingavg = 0;
		}
	}
	template<uint32 LengthofAverage, typename T>
	inline bool RollingAverage<LengthofAverage, T>::GetAvg(T& output)
	{
		if (iterator != 0)
			return false;
		output = m_buff;
		return true;
	}
}