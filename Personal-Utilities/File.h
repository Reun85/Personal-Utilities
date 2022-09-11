#pragma once

#include <string>
namespace Reun::Utils::File
{
	void UtilsCreateDirectory(const std::string_view& inp);
	void UtilsCreateDirectories(const std::string_view& inp);
}
namespace Reun::Utils
{
	using namespace File;
}