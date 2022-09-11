#include "JSON.h"
#include <unordered_set>

namespace Reun::Utils::Inner
{
	namespace Json {
		int findinstringkeeptrackofcharcount(const std::string& inp, int start, const std::unordered_set<char>& inc, int& linec, int& charcount)
		{
			while (start<inp.size())
			{
				const char& temp = inp[start];
				if (temp == '\n')
				{
					linec++;
					charcount = 0;
				}
				else if (temp != '\t')
				{
					charcount++;
				}
				if (inc.contains(temp))
					return start;
				
				start++;
			}
			return -1;
		}
		/// <summary>
		/// can be decimal or integer
		/// </summary>
		/// <param name="inp"></param>
		/// <returns> -1 means err</returns>
		int findendofnum(const std::string_view& inp, int start, int& linec, int& charc)
		{
			while ((inp[start] >= '0' && inp[start] <= '9') || (inp[start] == '.' || inp[start] == ','))
			{
				start++;
				charc++;
				if (start == inp.size())
					return -1;
			}
			return start;
		}
		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="Logger"></typeparam>
		/// <typeparam name="LOG"></typeparam>
		/// <returns>-1 means err</returns>
		int findendofstring(const std::string_view& inp, int start, int& linec, int& charc)
		{
			start++;
			while (inp[start] != '"')
			{
				if (inp[start] == '\n')
				{
					linec++;
					charc = 0;
				}
				else if (inp[start] == '\\')
				{
					
				}
			}
		}
	}

}

namespace Reun::Utils
{
	template<std::ostream& Logger,bool LOG>
	constexpr JSON<Logger, LOG>::JSON()
	{
	}
	template<std::ostream& Logger, bool LOG>
	JSON<Logger,LOG>::JSON(const std::string& filename)
	{	
		std::ifstream read;
		read.open(filename.c_str());
		std::string val((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
		read.close();
		std::cout << val;
		open(val);
	}
	template<std::ostream& Logger, bool LOG>
	constexpr static JSON<Logger,LOG> JSON<Logger,LOG>::JSONfromstring(const std::string_view& inp)
	{
		JSON js;
		js.open(inp);
		return std::move(js);
	}	
	template<std::ostream& Logger, bool LOG>
	std::optional<std::vector<typename JSON<Logger, LOG>::Field>&> JSON<Logger, LOG>::Field::GetArray()
	{
		if (type == Array)
			return std::optional<std::vector<typename JSON<Logger>::Field>&>{val.arr};
		if(LOG)
			Logger << "ERROR! Value was expected to be a " << FieldType::Array << " yet it was " << type;
		return std::nullopt;
	}
	template<std::ostream& Logger, bool LOG>
	std::optional<typename JSON<Logger, LOG>::Object&> JSON<Logger, LOG>::Field::GetObject()
	{
		if (type == Obj)
			return std::optional<std::vector<typename JSON<Logger>::Field>&>{val.arr};
		if (LOG)
			Logger << "ERROR! Value was expected to be a " << FieldType::Obj << " yet it was " << type;
		return std::nullopt;
	}
	template<std::ostream& Logger, bool LOG>
	std::optional<std::string&> JSON<Logger, LOG>::Field::GetString()
	{
		if (type == String)
			return std::optional<std::vector<typename JSON<Logger>::Field>&>{val.arr};
		if (LOG)
			Logger << "ERROR! Value was expected to be a " << FieldType::String << " yet it was " << type;
		return std::nullopt;
	}
	template<std::ostream& Logger, bool LOG>
	std::optional<long long> JSON<Logger, LOG>::Field::GetNumber()
	{
		if (type == Integer)
			return std::optional<std::vector<typename JSON<Logger>::Field>&>{val.arr};
		if (LOG)
			Logger << "ERROR! Value was expected to be a " << FieldType::Integer << " yet it was " << type;
		return std::nullopt;
	}
	template<std::ostream& Logger, bool LOG>
	std::optional<bool> JSON<Logger, LOG>::Field::GetBoolean()
	{
		if (type == Boolean)
			return std::optional<std::vector<typename JSON<Logger>::Field>&>{val.arr};
		if (LOG)
			Logger << "ERROR! Value was expected to be a " << FieldType::Boolean << " yet it was " << type;
		return std::nullopt;
	}
	template<std::ostream& Logger, bool LOG>
	std::optional<float> JSON<Logger, LOG>::Field::GetDecimal()
	{
		if (type == Decimal)
			return std::optional<std::vector<typename JSON<Logger>::Field>&>{val.arr};
		if (LOG)
			Logger << "ERROR! Value was expected to be a " << FieldType::Decimal << " yet it was " << type;
		return std::nullopt;
	}
	template<std::ostream& Logger, bool LOG>
	constexpr void JSON<Logger, LOG>::open(const std::string_view& inp) {

		int linec = 0;
		recurse(inp,0,  linec, root, Field::FieldType::Null);
	}
	template<std::ostream& Logger, bool LOG>
	void JSON<Logger, LOG>::recurse(const std::string_view& inp, int cont, int& linec, Field& curr, Field::FieldType outside)
	{
		enum whatdidwefind {OBJ, ARR, STR,OTH};
		whatdidwefind found;
		bool end = true;
		int currchar = 0;
		int prevline;
		int prevchar;
		while (end)
		{
			const char& temp = inp[cont];
			//find stuff we care about
			if (temp == '\n')
			{
				linec++;
				currchar = 0;
			}
			else if (temp != '\t')
			{
				if (temp == '[') {
					found = ARR;
					end = true;
					prevline = linec;
					prevchar = currchar;
				}
				else if (temp == '{'){
					found = OBJ;
					end = true;
					prevline = linec;
					prevchar = currchar;
				}
				else if (temp == '"'){
					found = STR;
					end = true;
					prevline = linec;
					prevchar = currchar;
				}
				else
				{
					found = OTH;
					end = true;
					prevline = linec;
					prevchar = currchar;
				}
				currchar++;
			}

			cont++;
		}

		if (found == OTH)//meaning number or something random, gotta find end. ONLY VALID IN ARR
		{
			if (outside != ARR)
			{
				if (LOG)
					Logger << "[JSON READER] Unexpected token at line: " << prevline << " character: " << prevchar;
				curr.type = Field::FieldType::Null;
				return;
			}
			cont = Inner::Json::findendofnum(inp, cont, linec, currchar);
			return;
			
		}
	}
}
