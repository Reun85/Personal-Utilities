
namespace Reun::Utils
{
	void UtilsCreateDirectory(const std::string_view& inp)
	{
		if (!std::filesystem::is_directory(inp))
		{
			std::filesystem::create_directory(inp);
		}
	}
	void UtilsCreateDirectories(const std::string_view& inp)
	{
		if (!std::filesystem::is_directory(inp))
		{
			std::filesystem::create_directories(inp);
		}
	}
}