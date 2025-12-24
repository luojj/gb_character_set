// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：FileSystem.h
// 创建日期：2021-09-22
// 创建人：罗俊杰
// 文件说明：对std::filesystem的封装
// $_FILEHEADER_END ***********************************************************

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <ctime>
#include <filesystem>
#include <list>
#include <tuple>
#include "TypeDef.h"

class CFileSystem
{
public:
	CFileSystem() = default;
	~CFileSystem() = default;

public:
	// 获取程序当前路径
	// 返回"C:\Windows\system.ini"
	static std::string GetCurrentPath();
	static std::string GetCurrentPath(bool abByProcess);
	static std::filesystem::path GetCurrentFilePath();

	// 获取路径的根名
	// 例如:C:\Windows\system.ini,返回"C:"
	static std::string GetRootName(const std::string& astrFilePath);
	static std::string GetRootName(const std::filesystem::path& aFilePath);

	// 获取路径的根路径
	// 例如:C:\Windows\system.ini,返回"C:"
	static std::string GetRootPath(const std::string& astrFilePath);
	static std::string GetRootPath(const std::filesystem::path& aFilePath);

	// 获取路径的根目录
	// 例如:C:\Windows\system.ini,返回"\"
	static std::string GetRootDirectory(const std::string& astrFilePath);
	static std::string GetRootDirectory(const std::filesystem::path& aFilePath);

	// 获取相对根路径的路径
	// 例如:C:\Windows\system.ini,返回"Windows\system.ini"
	static std::string GetRelativePath(const std::string& astrFilePath);
	static std::string GetRelativePath(const std::filesystem::path& aFilePath);

	// 获取Parent路径的路径
	// 例如:C:\Windows\system.ini,返回"C:\Windows"
	static std::string GetParentPath(const std::string& astrFilePath);
	static std::string GetParentPath(const std::filesystem::path& aFilePath);

	// 获取文件名(不带扩展名)
	// 例如:C:\Windows\system.ini,返回"system"
	static std::string GetFileName(const std::string& astrFilePath);
	static std::string GetFileName(const std::filesystem::path& aFilePath);

	// 获取文件名(带扩展名)
	// 例如:C:\Windows\system.ini,返回"system.ini"
	static std::string GetFullFileName(const std::string& astrFilePath);
	static std::string GetFullFileName(const std::filesystem::path& aFilePath);

	// 获取文件扩展名
	// 例如:C:\Windows\system.ini,返回"ini"
	static std::string GetExtensionName(const std::string& astrFilePath);
	static std::string GetExtensionName(const std::filesystem::path& aFilePath);

	// 替换文件名
	// 例如:C:\Windows\system.ini,新文件名"111",返回"C:\Windows\111"
	static std::string ReplaceFileName(const std::string& astrFilePath, const std::string& astrNewName);
	static std::string ReplaceFileName(std::filesystem::path& aFilePath, const std::string& astrNewName);

	// 替换扩展名
	// 例如:C:\Windows\system.ini,新扩展名"log",返回"C:\Windows\system.log"
	static std::string ReplaceExtension(const std::string& astrFilePath, const std::string& astrNewName);
	static std::string ReplaceExtension(std::filesystem::path& aFilePath, const std::string& astrNewName);

	// 移除单个通用格式文件名
	// 例如:C:\Windows\system.ini,返回"C:\Windows\"
	static std::string RemoveFileName(const std::string& astrFilePath);
	static std::string RemoveFileName(std::filesystem::path& aFilePath);

	// 文件或目录是否存在
	static bool IsExists(const std::string& astrFilePath) noexcept;

	// 是否为目录
	static bool IsDirectory(const std::string& astrFilePath) noexcept;

	// 是否为一个文件
	static bool IsRegularFile(const std::string& astrFilePath) noexcept;

	// 是否为空
	// 对于目录,如果目录下无文件返回true,否则返回false,不存在目录时也返回false,
	// 例如:"D:\\2\\1",目录2存在,目录1不存在,则返回false
	// 对于文件,文件无内容返回true,否则返回false
	static bool IsEmpty(const std::string& astrFilePath);

	// 创建目录
	static bool CreateSystemDirectory(const std::string& astrFilePath) noexcept;

	// 创建多级目录
	static bool CreateSystemDirectorys(const std::string& astrFilePath);

	// 删除文件或空目录
	static bool RemoveFile(const std::string& astrFilePath) noexcept;

	// 递归删除目录及目录下的所有文件
	static bool RemoveDirectorys(const std::string & astrFilePath);

	// 拷贝文件(不能拷贝目录)
	static bool CopyFile(const std::string& astrSrcFilePath, const std::string& astrDstFilePath);

	// 递归拷贝目录
	static void CopyDirectory(const std::string& astrSrcFilePath, const std::string& astrDstFilePath, bool abCopyFile);

	// 递归获取目录下的所有文件路径
	static std::list<std::tuple<std::string, std::string, std::string>> GetFilePaths(const std::string& astrFilePath, bool abContainDirectory);

	// 重命名文件
	static void RenameFile(const std::string& astrSrcFilePath, const std::string& astrDstFilePath) noexcept;

	// 获取文件大小
	static MyUInt64 GetFileSize(const std::string& astrFilePath) noexcept;

	// 获取文件修改时间
	static std::time_t GetFileModifyTime(const std::string& astrFilePath) noexcept;
};

#endif