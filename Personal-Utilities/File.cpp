#include "LNpch.h"
#include "File.h"

namespace Leon::Utils
{
	void UtilsCreateDirectory(const char* inp)
	{
		if (!std::filesystem::is_directory(inp))
		{
			std::filesystem::create_directory(inp);
		}
	}
	void UtilsCreateDirectories(const char* inp)
	{
		if (!std::filesystem::is_directory(inp))
		{
			std::filesystem::create_directories(inp);
		}
	}
}