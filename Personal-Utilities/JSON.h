#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <optional>
#include <unordered_map>

#include "typedefs.h"

namespace Reun::Utils {
	template<std::ostream& Logger = std::cout,const bool LOG = false>
	class JSON
	{

		class Object;
		class Field
		{
		public:
			bool IsNull() { return type == Null; }		
			void* GetValue() { return &val; }
			std::optional<Object&> GetObject();
			std::optional<std::vector<Field>&> GetArray();
			std::optional<std::string&> GetString();
			std::optional<bool> GetBoolean();
			std::optional<long long> GetNumber();
			std::optional<float> GetDecimal();
		private:
			enum FieldType : uint8 { Obj, Array, String, Boolean, Integer, Decimal, Null };
			FieldType type;
			union val{
				Object fi;
				std::vector<Field> arr;
				std::string str;
				bool b;
				long long num;
				float dec;
			};
			friend JSON;
		};
		class Object
		{
			std::unordered_map<std::string, Field> values;
		};
	public:
		constexpr void open(const std::string_view& inp);
		JSON(const std::string& filename);
		constexpr static JSON JSONfromstring(const std::string_view& inp);
	private:
		JSON::Field root;
		void recurse(const std::string_view& inp,int cont, int& linec, Field& curr, Field::FieldType outside);
		constexpr JSON();
		
	};
}