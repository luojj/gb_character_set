#if defined (_WIN32)
#include <Windows.h>
#endif
#include <chrono>
#include "File/FileSystem.h"

// 获取程序当前路径
std::string CFileSystem::GetCurrentPath()
{
	std::filesystem::path Path = GetCurrentFilePath();
	return (Path.empty() ? std::string{} : Path.string());
}

// 获取程序当前路径
std::string CFileSystem::GetCurrentPath(bool abByProcess)
{
	// Windows系统下以服务启动程序时,CFileSystem::GetCurrentPath()返回的是"C:\WINDOWS\system32",所以需要使用其它函数
	std::string strReturn;
	if (abByProcess)
	{
		strReturn = CFileSystem::GetCurrentPath();
	}
	else
	{
#if defined (_WIN32)
		char szPath[_MAX_PATH]{};
		if (GetModuleFileNameA(nullptr, szPath, _MAX_PATH) == 0)
			return std::string{};

		std::string strPath = szPath;
		strReturn = CFileSystem::GetParentPath(strPath);
#endif
	}
	return strReturn;
}

// 获取程序当前路径
std::filesystem::path CFileSystem::GetCurrentFilePath()
{
	std::error_code ErrorCode{};
	return std::filesystem::current_path(ErrorCode);
}

// 获取路径的根名
std::string CFileSystem::GetRootName(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_root_name() ? std::string{} : Path.root_name().string());
}

// 获取路径的根名
std::string CFileSystem::GetRootName(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_root_name() ? std::string{} : aFilePath.root_name().string());
}

// 获取路径的根路径
std::string CFileSystem::GetRootPath(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_root_path() ? std::string{} : Path.root_path().string());
}

// 获取路径的根路径
std::string CFileSystem::GetRootPath(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_root_path() ? std::string{} : aFilePath.root_path().string());
}

// 获取路径的根目录
std::string CFileSystem::GetRootDirectory(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_root_directory() ? std::string{} : Path.root_directory().string());
}

// 获取路径的根目录
std::string CFileSystem::GetRootDirectory(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_root_directory() ? std::string{} : aFilePath.root_directory().string());
}

// 获取相对根路径的路径
std::string CFileSystem::GetRelativePath(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_relative_path() ? std::string{} : Path.relative_path().string());
}

// 获取相对根路径的路径
std::string CFileSystem::GetRelativePath(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_relative_path() ? std::string{} : aFilePath.relative_path().string());
}

// 获取Parent路径的路径
std::string CFileSystem::GetParentPath(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_parent_path() ? std::string{} : Path.parent_path().string());
}

// 获取Parent路径的路径
std::string CFileSystem::GetParentPath(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_parent_path() ? std::string{} : aFilePath.parent_path().string());
}

// 获取文件名(不带扩展名)
std::string CFileSystem::GetFileName(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_stem() ? std::string{} : Path.stem().string());
}

// 获取文件名(不带扩展名)
std::string CFileSystem::GetFileName(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_stem() ? std::string{} : aFilePath.stem().string());
}

// 获取文件名(带扩展名)
std::string CFileSystem::GetFullFileName(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_filename() ? std::string{} : Path.filename().string());
}

// 获取文件名(带扩展名)
std::string CFileSystem::GetFullFileName(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_filename() ? std::string{} : aFilePath.filename().string());
}

// 获取文件扩展名
std::string CFileSystem::GetExtensionName(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return (!Path.has_extension() ? std::string{} : Path.extension().string());
}

// 获取文件扩展名
std::string CFileSystem::GetExtensionName(const std::filesystem::path& aFilePath)
{
	if (aFilePath.empty())
		return std::string{};
	return (!aFilePath.has_extension() ? std::string{} : aFilePath.extension().string());
}

// 替换文件名
std::string CFileSystem::ReplaceFileName(const std::string& astrFilePath, const std::string& astrNewName)
{
	std::filesystem::path Path(astrFilePath);
	return Path.replace_filename(astrNewName).string();
}

// 替换文件名
std::string CFileSystem::ReplaceFileName(std::filesystem::path& aFilePath, const std::string& astrNewName)
{
	return (aFilePath.empty() ? std::string{} : aFilePath.replace_filename(astrNewName).string());
}

// 替换扩展名
std::string CFileSystem::ReplaceExtension(const std::string& astrFilePath, const std::string& astrNewName)
{
	std::filesystem::path Path(astrFilePath);
	return Path.replace_extension(astrNewName).string();
}

// 替换扩展名
std::string CFileSystem::ReplaceExtension(std::filesystem::path& aFilePath, const std::string& astrNewName)
{
	return (aFilePath.empty() ? std::string{} : aFilePath.replace_extension(astrNewName).string());
}

// 移除单个通用格式文件名
std::string CFileSystem::RemoveFileName(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	return Path.remove_filename().string();
}

// 移除单个通用格式文件名
std::string CFileSystem::RemoveFileName(std::filesystem::path& aFilePath)
{
	return (aFilePath.empty() ? std::string{} : aFilePath.remove_filename().string());
}

// 文件或目录是否存在
bool CFileSystem::IsExists(const std::string& astrFilePath) noexcept
{
	// 检测文件或目录是否存在
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::exists(Path, ErrorCode);
}

// 是否为目录
bool CFileSystem::IsDirectory(const std::string& astrFilePath) noexcept
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::is_directory(Path, ErrorCode);
}

// 是否为一个文件
bool CFileSystem::IsRegularFile(const std::string& astrFilePath) noexcept
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::is_regular_file(Path, ErrorCode);
}

// 是否为空
bool CFileSystem::IsEmpty(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::is_empty(Path, ErrorCode);
}

// 创建目录
bool CFileSystem::CreateSystemDirectory(const std::string& astrFilePath) noexcept
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::create_directory(Path, ErrorCode);
}

// 创建多级目录
bool CFileSystem::CreateSystemDirectorys(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::create_directories(Path, ErrorCode);
}

// 删除文件或空目录
bool CFileSystem::RemoveFile(const std::string& astrFilePath) noexcept
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::remove(Path, ErrorCode);
}

// 递归删除目录及目录下的所有文件
bool CFileSystem::RemoveDirectorys(const std::string& astrFilePath)
{
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	return (std::filesystem::remove_all(Path, ErrorCode) == static_cast<std::uintmax_t>(-1) ? false : true);
}

// 拷贝文件(不能拷贝目录)
bool CFileSystem::CopyFile(const std::string& astrSrcFilePath, const std::string& astrDstFilePath)
{
	std::filesystem::path SrcFilePath(astrSrcFilePath);
	std::filesystem::path DstFilePath(astrDstFilePath);
	std::error_code ErrorCode{};
	return std::filesystem::copy_file(SrcFilePath, DstFilePath, std::filesystem::copy_options::overwrite_existing, ErrorCode);
}

// 递归拷贝目录
void CFileSystem::CopyDirectory(const std::string& astrSrcFilePath, const std::string& astrDstFilePath, bool abCopyFile)
{
	std::filesystem::path SrcFilePath(astrSrcFilePath);
	std::filesystem::path DstFilePath(astrDstFilePath);
	std::error_code ErrorCode{};
	std::filesystem::copy_options copyOptions;
	if (abCopyFile)
		copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
	else
		copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive | std::filesystem::copy_options::directories_only;
	std::filesystem::copy(SrcFilePath, DstFilePath, copyOptions, ErrorCode);
}

// 递归获取目录下的所有文件路径
std::list<std::tuple<std::string, std::string, std::string>> CFileSystem::GetFilePaths(const std::string& astrFilePath, bool abContainDirectory)
{
	std::list<std::tuple<std::string, std::string, std::string>> files{};
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	for (const auto& entry : std::filesystem::recursive_directory_iterator(Path, ErrorCode))
	{
		if (abContainDirectory)
		{
			files.emplace_back(std::make_tuple(entry.path().parent_path().string(), entry.path().filename().string(), entry.path().string()));
		}
		else
		{
			if (!entry.is_directory())
				files.emplace_back(std::make_tuple(entry.path().parent_path().string(), entry.path().filename().string(), entry.path().string()));
		}
	}
	return files;
}

// 重命名文件
void CFileSystem::RenameFile(const std::string& astrSrcFilePath, const std::string& astrDstFilePath) noexcept
{
	std::filesystem::path SrcFilePath(astrSrcFilePath);
	std::filesystem::path DstFilePath(astrDstFilePath);
	std::error_code ErrorCode{};
	std::filesystem::rename(SrcFilePath, DstFilePath, ErrorCode);
}

// 获取文件大小
MyUInt64 CFileSystem::GetFileSize(const std::string& astrFilePath) noexcept
{
	// 当前为目录
	std::filesystem::path Path(astrFilePath);
	if (std::filesystem::is_directory(Path))
		return 0;

	std::error_code ErrorCode{};
	return (MyUInt64)std::filesystem::file_size(Path, ErrorCode);
}

// 获取文件修改时间
std::time_t CFileSystem::GetFileModifyTime(const std::string& astrFilePath) noexcept
{
	// 因linux下g++ 9.3中未找到__std_fs_file_time_epoch_adjustment的定义,先自己定义一个常量
	constexpr MyUInt64 file_time_epoch_adjustment = 0x19DB1DED53E8000LL;
	std::filesystem::path Path(astrFilePath);
	std::error_code ErrorCode{};
	auto FileModifyTime = std::filesystem::last_write_time(Path, ErrorCode);
	if (FileModifyTime == (std::filesystem::file_time_type::min)())
		return 0;

	auto Ticks = FileModifyTime.time_since_epoch().count() - file_time_epoch_adjustment;
	auto TimePoint = std::chrono::system_clock::time_point(std::chrono::system_clock::time_point::duration(Ticks));
	std::time_t FileModifyTime_t = std::chrono::system_clock::to_time_t(TimePoint);
	return FileModifyTime_t;
}