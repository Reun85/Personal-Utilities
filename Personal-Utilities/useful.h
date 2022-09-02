#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>


namespace help {
	using namespace std;
	template<typename T>
	struct quoteprint : std::false_type {};

template<>
struct quoteprint<char*> : std::true_type{};
template<>
struct quoteprint<const char*> : std::true_type{};
template<>
struct quoteprint<string> : std::true_type{};

	template<typename T>
	struct outputstream_compatible : std::false_type {};

	template<typename T>
	struct outputstream_compatible<vector<T>> : std::true_type {};
	template<typename T>
	struct outputstream_compatible<unordered_set<T>> : std::true_type {};
	template<typename T, typename U>
	struct outputstream_compatible<unordered_map<T, U>> : std::true_type {};

	template<typename T>
	std::ostream& PrintData(std::ostream& os, const T& val)
	{		
		os << val;
		return os;
	}
	template<typename T> requires quoteprint<T>::value
	std::ostream& PrintData(std::ostream& os, const T& val)
	{
		os << "\"" << val << "\"";
		return os;
	}
	template<typename T,typename U, typename Q> requires std::is_same<T, std::pair<U,Q>>::value
	std::ostream& PrintData(std::ostream& os, const T& val)
	{
		os << "{ " << PrintData(os,val.first) << " - " << PrintData(os, val.second) << " }";
		return os;
	}

	template<typename T> requires outputstream_compatible<T>::value
		std::ostream& operator<<(std::ostream& os, const T& v)
	{
		static_assert(outputstream_compatible<T>(),"Invalid Type.");
		if (v.size() == 0)
		{
			os << "[]";
			return os;
		}
		os << "[ ";
		for (int i = 0; i < v.size()-1; i++)
		{
			PrintData(os, v.at(i));
			os << ", ";
		}
		PrintData(os, v.at(v.size()-1));
		os << " ]";
		return os;
	}
}