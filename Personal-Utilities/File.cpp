#include <string>
#include <filesystem>
#include "File.h"
void Reun::Utils::File::UtilsCreateDirectory(const std::string_view& inp)
{
	if (!std::filesystem::is_directory(inp))
	{
		std::filesystem::create_directory(inp);
	}
}
void Reun::Utils::File::UtilsCreateDirectories(const std::string_view& inp)
{
	if (!std::filesystem::is_directory(inp))
	{
		std::filesystem::create_directories(inp);
	}
}