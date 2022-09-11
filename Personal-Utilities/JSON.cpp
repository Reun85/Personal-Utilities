#include "JSON.h"


namespace Reun::Utils::JSONREADER
{

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
			char& temp = inp[cont];
			//find stuff we care about
			if (temp == '\n')
			{
				linec++;
				currchar = 0;
			}
			else if (!(temp == '\t' || temp == ' '))
			{
				if (temp == '[') {
					found = ARR;
					end = true;
					prevline = linec;
					prechar = currchar;
				}
				else if (temp == '{'){
					found = OBJ;
					end = true;
					prevline = linec;
					prechar = currchar;
				}
				else if (temp == '"'){
					found = STR;
					end = true;
					prevline = linec;
					prechar = currchar;
				}
				else
				{
					found = OTH;
					end = true;
					prevline = linec;
					prechar = currchar;
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
				return;
			}
			
			
		}
	}
}
