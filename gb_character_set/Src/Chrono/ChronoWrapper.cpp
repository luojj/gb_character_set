#include <format>
#include <sstream>
#include "Chrono/ChronoWrapper.h"

// 各类时间转毫秒
constexpr std::time_t S_TO_MS = 1000;
constexpr std::time_t M_TO_MS = 60 * 1000;
constexpr std::time_t H_TO_MS = 60 * 60 * 1000;
constexpr std::time_t D_TO_MS = 24 * 60 * 60 * 1000;

// 获取毫秒级时间
std::time_t CChronoWrapper::MS_Time(ENUM_CLOCK_TYPE aClock)
{
	std::time_t iNowTime = 0;
	if (aClock == ENUM_CLOCK_TYPE::System)
		iNowTime = crn::time_point_cast<crn::milliseconds>(system_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::Steady)
		iNowTime = crn::time_point_cast<crn::milliseconds>(steady_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::High_Resolution)
		iNowTime = crn::time_point_cast<crn::milliseconds>(high_resolution_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::File)
		iNowTime = crn::time_point_cast<crn::milliseconds>(file_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::GPS)
		iNowTime = crn::time_point_cast<crn::milliseconds>(gps_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::UTC)
		iNowTime = crn::time_point_cast<crn::milliseconds>(utc_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::TAI)
		iNowTime = crn::time_point_cast<crn::milliseconds>(tai_c::now()).time_since_epoch().count();
	return iNowTime;
}

// 获取秒级时间
std::time_t CChronoWrapper::S_Time(ENUM_CLOCK_TYPE aClock)
{
	std::time_t iNowTime = 0;
	if (aClock == ENUM_CLOCK_TYPE::System)
		iNowTime = crn::time_point_cast<crn::seconds>(system_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::Steady)
		iNowTime = crn::time_point_cast<crn::seconds>(steady_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::High_Resolution)
		iNowTime = crn::time_point_cast<crn::seconds>(high_resolution_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::File)
		iNowTime = crn::time_point_cast<crn::seconds>(file_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::GPS)
		iNowTime = crn::time_point_cast<crn::seconds>(gps_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::UTC)
		iNowTime = crn::time_point_cast<crn::seconds>(utc_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::TAI)
		iNowTime = crn::time_point_cast<crn::seconds>(tai_c::now()).time_since_epoch().count();
	return iNowTime;
}

// 获取分钟级时间
std::time_t CChronoWrapper::M_Time(ENUM_CLOCK_TYPE aClock)
{
	std::time_t iNowTime = 0;
	if (aClock == ENUM_CLOCK_TYPE::System)
		iNowTime = crn::time_point_cast<crn::minutes>(system_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::Steady)
		iNowTime = crn::time_point_cast<crn::minutes>(steady_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::High_Resolution)
		iNowTime = crn::time_point_cast<crn::minutes>(high_resolution_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::File)
		iNowTime = crn::time_point_cast<crn::minutes>(file_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::GPS)
		iNowTime = crn::time_point_cast<crn::minutes>(gps_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::UTC)
		iNowTime = crn::time_point_cast<crn::minutes>(utc_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::TAI)
		iNowTime = crn::time_point_cast<crn::minutes>(tai_c::now()).time_since_epoch().count();
	return iNowTime;
}

// 获取小时级时间
std::time_t CChronoWrapper::H_Time(ENUM_CLOCK_TYPE aClock)
{
	std::time_t iNowTime = 0;
	if (aClock == ENUM_CLOCK_TYPE::System)
		iNowTime = crn::time_point_cast<crn::hours>(system_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::Steady)
		iNowTime = crn::time_point_cast<crn::hours>(steady_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::High_Resolution)
		iNowTime = crn::time_point_cast<crn::hours>(high_resolution_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::File)
		iNowTime = crn::time_point_cast<crn::hours>(file_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::GPS)
		iNowTime = crn::time_point_cast<crn::hours>(gps_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::UTC)
		iNowTime = crn::time_point_cast<crn::hours>(utc_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::TAI)
		iNowTime = crn::time_point_cast<crn::hours>(tai_c::now()).time_since_epoch().count();
	return iNowTime;
}

// 获取天级时间
std::time_t CChronoWrapper::D_Time(ENUM_CLOCK_TYPE aClock)
{
	std::time_t iNowTime = 0;
	if (aClock == ENUM_CLOCK_TYPE::System)
		iNowTime = crn::time_point_cast<crn::days>(system_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::Steady)
		iNowTime = crn::time_point_cast<crn::days>(steady_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::High_Resolution)
		iNowTime = crn::time_point_cast<crn::days>(high_resolution_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::File)
		iNowTime = crn::time_point_cast<crn::days>(file_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::GPS)
		iNowTime = crn::time_point_cast<crn::days>(gps_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::UTC)
		iNowTime = crn::time_point_cast<crn::days>(utc_c::now()).time_since_epoch().count();
	else if (aClock == ENUM_CLOCK_TYPE::TAI)
		iNowTime = crn::time_point_cast<crn::days>(tai_c::now()).time_since_epoch().count();
	return iNowTime;
}

// 系统时间转换为utc_clock
utc_c::time_point CChronoWrapper::SystemToUTC(const system_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用from_sys
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return crn::clock_cast<utc_c>(aTimePoint);
}

// 系统时间转换为utc_clock的毫秒
std::time_t CChronoWrapper::SystemToUTC_MS(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(SystemToUTC(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为utc_clock的秒
std::time_t CChronoWrapper::SystemToUTC_S(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(SystemToUTC(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为utc_clock的分钟
std::time_t CChronoWrapper::SystemToUTC_M(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(SystemToUTC(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为utc_clock的小时
std::time_t CChronoWrapper::SystemToUTC_H(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(SystemToUTC(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为utc_clock的天
std::time_t CChronoWrapper::SystemToUTC_D(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(SystemToUTC(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为file_clock
file_c::time_point CChronoWrapper::SystemToFile(const system_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用from_utc
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return crn::clock_cast<file_c>(SystemToUTC(aTimePoint));
}

// 系统时间转换为file_clock的毫秒
std::time_t CChronoWrapper::SystemToFile_MS(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(SystemToFile(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为file_clock的秒
std::time_t CChronoWrapper::SystemToFile_S(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(SystemToFile(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为file_clock的分钟
std::time_t CChronoWrapper::SystemToFile_M(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(SystemToFile(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为file_clock的小时
std::time_t CChronoWrapper::SystemToFile_H(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(SystemToFile(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为file_clock的天
std::time_t CChronoWrapper::SystemToFile_D(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(SystemToFile(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为gps_clock
gps_c::time_point CChronoWrapper::SystemToGPS(const system_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用from_utc
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return crn::clock_cast<gps_c>(SystemToUTC(aTimePoint));
}

// 系统时间转换为gps_clock的毫秒
std::time_t CChronoWrapper::SystemToGPS_MS(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(SystemToGPS(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为gps_clock的秒
std::time_t CChronoWrapper::SystemToGPS_S(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(SystemToGPS(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为gps_clock的分钟
std::time_t CChronoWrapper::SystemToGPS_M(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(SystemToGPS(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为gps_clock的小时
std::time_t CChronoWrapper::SystemToGPS_H(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(SystemToGPS(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为gps_clock的天
std::time_t CChronoWrapper::SystemToGPS_D(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(SystemToGPS(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为tai_clock
tai_c::time_point CChronoWrapper::SystemToTAI(const system_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用from_utc
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return crn::clock_cast<tai_c>(SystemToUTC(aTimePoint));
}

// 系统时间转换为tai_clock的毫秒
std::time_t CChronoWrapper::SystemToTAI_MS(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(SystemToTAI(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为tai_clock的秒
std::time_t CChronoWrapper::SystemToTAI_S(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(SystemToTAI(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为tai_clock的分钟
std::time_t CChronoWrapper::SystemToTAI_M(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(SystemToTAI(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为tai_clock的小时
std::time_t CChronoWrapper::SystemToTAI_H(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(SystemToTAI(aTimePoint)).time_since_epoch().count();
}

// 系统时间转换为tai_clock的天
std::time_t CChronoWrapper::SystemToTAI_D(const system_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(SystemToTAI(aTimePoint)).time_since_epoch().count();
}

// utc_clock转换为系统时间
system_c::time_point CChronoWrapper::UTCToSystem(const utc_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用to_sys
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return crn::clock_cast<system_c>(aTimePoint);
}

// utc_clock转换为系统时间的毫秒
std::time_t CChronoWrapper::UTCToSystem_MS(const utc_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(UTCToSystem(aTimePoint)).time_since_epoch().count();
}

// utc_clock转换为系统时间的秒
std::time_t CChronoWrapper::UTCToSystem_S(const utc_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(UTCToSystem(aTimePoint)).time_since_epoch().count();
}

// utc_clock转换为系统时间的分钟
std::time_t CChronoWrapper::UTCToSystem_M(const utc_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(UTCToSystem(aTimePoint)).time_since_epoch().count();
}

// utc_clock转换为系统时间的小时
std::time_t CChronoWrapper::UTCToSystem_H(const utc_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(UTCToSystem(aTimePoint)).time_since_epoch().count();
}

// utc_clock转换为系统时间的天
std::time_t CChronoWrapper::UTCToSystem_D(const utc_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(UTCToSystem(aTimePoint)).time_since_epoch().count();
}

// file_clock转换为系统时间
system_c::time_point CChronoWrapper::FileToSystem(const file_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用to_uts
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return UTCToSystem(crn::clock_cast<utc_c>(aTimePoint));
}

// file_clock转换为系统时间的毫秒
std::time_t CChronoWrapper::FileToSystem_MS(const file_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(FileToSystem(aTimePoint)).time_since_epoch().count();
}

// file_clock转换为系统时间的秒
std::time_t CChronoWrapper::FileToSystem_S(const file_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(FileToSystem(aTimePoint)).time_since_epoch().count();
}

// file_clock转换为系统时间的分钟
std::time_t CChronoWrapper::FileToSystem_M(const file_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(FileToSystem(aTimePoint)).time_since_epoch().count();
}

// file_clock转换为系统时间的小时
std::time_t CChronoWrapper::FileToSystem_H(const file_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(FileToSystem(aTimePoint)).time_since_epoch().count();
}

// file_clock转换为系统时间的天
std::time_t CChronoWrapper::FileToSystem_D(const file_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(FileToSystem(aTimePoint)).time_since_epoch().count();
}

// gps_clock转换为系统时间
system_c::time_point CChronoWrapper::GPSToSystem(const gps_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用to_uts
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return UTCToSystem(crn::clock_cast<utc_c>(aTimePoint));
}

// gps_clock转换为系统时间的毫秒
std::time_t CChronoWrapper::GPSToSystem_MS(const gps_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(GPSToSystem(aTimePoint)).time_since_epoch().count();
}

// gps_clock转换为系统时间的秒
std::time_t CChronoWrapper::GPSToSystem_S(const gps_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(GPSToSystem(aTimePoint)).time_since_epoch().count();
}

// gps_clock转换为系统时间的分钟
std::time_t CChronoWrapper::GPSToSystem_M(const gps_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(GPSToSystem(aTimePoint)).time_since_epoch().count();
}

// gps_clock转换为系统时间的小时
std::time_t CChronoWrapper::GPSToSystem_H(const gps_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(GPSToSystem(aTimePoint)).time_since_epoch().count();
}

// gps_clock转换为系统时间的天
std::time_t CChronoWrapper::GPSToSystem_D(const gps_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(GPSToSystem(aTimePoint)).time_since_epoch().count();
}

// tai_clock转换为系统时间
system_c::time_point CChronoWrapper::TAIToSystem(const tai_c::time_point& aTimePoint)
{
	// 建议使用clock_cast转换时钟之间的时间点,而不是直接调用to_uts
	// 因为ISO C++标准允许此类型定义to_utc和from_utc或to_sys和from_sys.
	// 由于具体实现内容可能因供应商而异,因此可以改用所有库供应商都提供的clock_cast.
	return UTCToSystem(crn::clock_cast<utc_c>(aTimePoint));
}

// tai_clock转换为系统时间的毫秒
std::time_t CChronoWrapper::TAIToSystem_MS(const tai_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::milliseconds>(TAIToSystem(aTimePoint)).time_since_epoch().count();
}

// tai_clock转换为系统时间的秒
std::time_t CChronoWrapper::TAIToSystem_S(const tai_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::seconds>(TAIToSystem(aTimePoint)).time_since_epoch().count();
}

// tai_clock转换为系统时间的分钟
std::time_t CChronoWrapper::TAIToSystem_M(const tai_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::minutes>(TAIToSystem(aTimePoint)).time_since_epoch().count();
}

// tai_clock转换为系统时间的小时
std::time_t CChronoWrapper::TAIToSystem_H(const tai_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::hours>(TAIToSystem(aTimePoint)).time_since_epoch().count();
}

// tai_clock转换为系统时间的天
std::time_t CChronoWrapper::TAIToSystem_D(const tai_c::time_point& aTimePoint)
{
	return crn::time_point_cast<crn::days>(TAIToSystem(aTimePoint)).time_since_epoch().count();
}

// system_clock转换为time_t
std::time_t CChronoWrapper::SystemToTime(system_c::time_point aTimePoint)
{
	return system_c::to_time_t(aTimePoint);
}

// time_t转换为system_clock
system_c::time_point CChronoWrapper::TimeToSystem(std::time_t aTime)
{
	return system_c::from_time_t(aTime);
}

// system的time_t(毫秒)转换为system_clock
system_c::time_point CChronoWrapper::System_MSToSystem(std::time_t aTime)
{
	return crn::sys_time<crn::milliseconds>{ crn::milliseconds{ aTime } };
}

// system的time_t(秒)转换为system_clock
system_c::time_point CChronoWrapper::System_SToSystem(std::time_t aTime)
{
	return System_MSToSystem(aTime * S_TO_MS);
}

// system的time_t(分钟)转换为system_clock
system_c::time_point CChronoWrapper::System_MToSystem(std::time_t aTime)
{
	return System_MSToSystem(aTime * M_TO_MS);
}

// system的time_t(小时)转换为system_clock
system_c::time_point CChronoWrapper::System_HToSystem(std::time_t aTime)
{
	return System_MSToSystem(aTime * H_TO_MS);
}

// system的time_t(天)转换为system_clock
system_c::time_point CChronoWrapper::System_DToSystem(std::time_t aTime)
{
	return System_MSToSystem(aTime * D_TO_MS);
}

// utc的time_t(毫秒)转换为system_clock
system_c::time_point CChronoWrapper::UTC_MSToSystem(std::time_t aTime)
{
	return UTCToSystem(crn::time_point<crn::utc_clock, crn::milliseconds>{ crn::milliseconds{ aTime } });
}

// utc的time_t(秒)转换为system_clock
system_c::time_point CChronoWrapper::UTC_SToSystem(std::time_t aTime)
{
	return UTC_MSToSystem(aTime * S_TO_MS);
}

// utc的time_t(分钟)转换为system_clock
system_c::time_point CChronoWrapper::UTC_MToSystem(std::time_t aTime)
{
	return UTC_MSToSystem(aTime * M_TO_MS);
}

// utc的time_t(小时)转换为system_clock
system_c::time_point CChronoWrapper::UTC_HToSystem(std::time_t aTime)
{
	return UTC_MSToSystem(aTime * H_TO_MS);
}

// utc的time_t(天)转换为system_clock
system_c::time_point CChronoWrapper::UTC_DToSystem(std::time_t aTime)
{
	return UTC_MSToSystem(aTime * D_TO_MS);
}

// file的time_t(毫秒)转换为system_clock
system_c::time_point CChronoWrapper::File_MSToSystem(std::time_t aTime)
{
	return FileToSystem(crn::time_point<crn::file_clock, crn::milliseconds>{ crn::milliseconds{ aTime } });
}

// file的time_t(秒)转换为system_clock
system_c::time_point CChronoWrapper::File_SToSystem(std::time_t aTime)
{
	return File_MSToSystem(aTime * S_TO_MS);
}

// file的time_t(分钟)转换为system_clock
system_c::time_point CChronoWrapper::File_MToSystem(std::time_t aTime)
{
	return File_MSToSystem(aTime * M_TO_MS);
}

// file的time_t(小时)转换为system_clock
system_c::time_point CChronoWrapper::File_HToSystem(std::time_t aTime)
{
	return File_MSToSystem(aTime * H_TO_MS);
}

// file的time_t(天)转换为system_clock
system_c::time_point CChronoWrapper::File_DToSystem(std::time_t aTime)
{
	return File_MSToSystem(aTime * D_TO_MS);
}

// gps的time_t(毫秒)转换为system_clock
system_c::time_point CChronoWrapper::GPS_MSToSystem(std::time_t aTime)
{
	return GPSToSystem(crn::time_point<crn::gps_clock, crn::milliseconds>{ crn::milliseconds{ aTime } });
}

// gps的time_t(秒)转换为system_clock
system_c::time_point CChronoWrapper::GPS_SToSystem(std::time_t aTime)
{
	return GPS_MSToSystem(aTime * S_TO_MS);
}

// gps的time_t(分钟)转换为system_clock
system_c::time_point CChronoWrapper::GPS_MToSystem(std::time_t aTime)
{
	return GPS_MSToSystem(aTime * M_TO_MS);
}

// gps的time_t(小时)转换为system_clock
system_c::time_point CChronoWrapper::GPS_HToSystem(std::time_t aTime)
{
	return GPS_MSToSystem(aTime * H_TO_MS);
}

// gps的time_t(天)转换为system_clock
system_c::time_point CChronoWrapper::GPS_DToSystem(std::time_t aTime)
{
	return GPS_MSToSystem(aTime * D_TO_MS);
}

// tai的time_t(毫秒)转换为system_clock
system_c::time_point CChronoWrapper::TAI_MSToSystem(std::time_t aTime)
{
	return TAIToSystem(crn::time_point<crn::tai_clock, crn::milliseconds>{ crn::milliseconds{ aTime } });
}

// tai的time_t(秒)转换为system_clock
system_c::time_point CChronoWrapper::TAI_SToSystem(std::time_t aTime)
{
	return TAI_MSToSystem(aTime * S_TO_MS);
}

// tai的time_t(分钟)转换为system_clock
system_c::time_point CChronoWrapper::TAI_MToSystem(std::time_t aTime)
{
	return TAI_MSToSystem(aTime * M_TO_MS);
}

// tai的time_t(小时)转换为system_clock
system_c::time_point CChronoWrapper::TAI_HToSystem(std::time_t aTime)
{
	return TAI_MSToSystem(aTime * H_TO_MS);
}

// tai的time_t(天)转换为system_clock
system_c::time_point CChronoWrapper::TAI_DToSystem(std::time_t aTime)
{
	return TAI_MSToSystem(aTime * D_TO_MS);
}

// 日期转换为系统时间
std::tuple<bool, crn::local_time<crn::system_clock::duration>> CChronoWrapper::DateTimeToSystem(uint32_t aiYear, uint32_t aiMonth, uint32_t aiDay, uint32_t aiHour, uint32_t aiMinute, uint32_t aiSecond, uint32_t aiMillisecond)
{
	crn::year_month_day ymd{ crn::year{ (int)aiYear } / crn::month{ aiMonth } / crn::day{ aiDay } };
	if (!ymd.ok())
		return std::make_tuple(false, crn::local_time<crn::system_clock::duration>{});

	crn::milliseconds ymd_d = crn::duration_cast<crn::milliseconds>(crn::sys_days(ymd).time_since_epoch());
	crn::milliseconds h_d = crn::duration_cast<crn::milliseconds>(crn::hours{ aiHour });
	crn::milliseconds m_d = crn::duration_cast<crn::milliseconds>(crn::minutes{ aiMinute });
	crn::milliseconds s_d = crn::duration_cast<crn::milliseconds>(crn::seconds{ aiSecond });
	crn::hh_mm_ss hms{ h_d + m_d + s_d + crn::milliseconds{ aiMillisecond } };
	return std::make_tuple(true, crn::local_time<crn::system_clock::duration>{ ymd_d + hms.to_duration() });
}

// 系统时间转换为日期
std::tuple<bool, crn::year_month_day, crn::hh_mm_ss<crn::milliseconds>, crn::year_month_weekday> CChronoWrapper::SystemToDateTime(const crn::local_time<crn::system_clock::duration>& aTimePoint)
{
	auto now_day = crn::floor<crn::days>(aTimePoint);
	crn::year_month_day ymd{ now_day };
	if (!ymd.ok())
		return std::make_tuple(false, crn::year_month_day{}, crn::hh_mm_ss<crn::milliseconds>{}, crn::year_month_weekday{});

	crn::year_month_weekday ymw = crn::sys_days(ymd);
	if (!ymw.ok())
		return std::make_tuple(false, crn::year_month_day{}, crn::hh_mm_ss<crn::milliseconds>{}, crn::year_month_weekday{});

	crn::hh_mm_ss<crn::milliseconds> hms{ crn::duration_cast<crn::milliseconds>(aTimePoint - now_day) };
	return std::make_tuple(true, ymd, hms, ymw);
}

// 获取下一个星期几
crn::local_time<crn::system_clock::duration> CChronoWrapper::NextWeekDay(uint32_t aiWeek)
{
	auto now = crn::zoned_time{ crn::current_zone(), system_c::now() }.get_local_time();
	crn::year_month_day ymd{ crn::floor<crn::days>(now) };
	crn::year_month_weekday ymw = crn::sys_days(ymd);

	uint32_t diff_day_t = 0;
	if (ymw.weekday().c_encoding() < aiWeek)
		diff_day_t = (aiWeek - ymw.weekday().c_encoding());
	else
		diff_day_t = 7 - (ymw.weekday().c_encoding() - aiWeek);

	now += crn::days{ diff_day_t };
	return now;
}

// 获取时间字符串
std::string CChronoWrapper::GetFormatTime(ENUM_TIME_FORMAT_TYPE aTimeFormatType, bool abUseZone, const system_c::time_point& aTime)
{
	// crn::current_zone()会在第一次使用时分配内存,但在程序退出时不会释放内存,
	// 导致内存泄漏检测工具会报内存泄漏,为避免不必要的错误,增加不使用crn::current_zone的处理机制
	if (abUseZone)
	{
		auto now = crn::zoned_time{ crn::current_zone()->name(), aTime }.get_local_time();
		auto now_millisecond = crn::time_point_cast<crn::milliseconds>(now);
		auto now_second = crn::floor<crn::seconds>(now_millisecond);
		auto now_day = crn::floor<crn::days>(now_millisecond);

		crn::year_month_day ymd{ now_day };
		crn::hh_mm_ss hms{ now_millisecond - now_day };

		auto year = (int32_t)ymd.year();
		auto month = (uint32_t)ymd.month();
		auto day = (uint32_t)ymd.day();
		auto hour = hms.hours().count();
		auto minute = hms.minutes().count();
		auto second = hms.seconds().count();
		auto millisecond = (now_millisecond - now_second).count();

		if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Date1)
			return std::format("{}{:02}{:02}", year, month, day);
		else if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Time1)
			return std::format("{}{:02}{:02}_{:02}{:02}{:02}", year, month, day, hour, minute, second);
		else if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Time2)
			return std::format("{}-{:02}-{:02} {:02}:{:02}:{:02}", year, month, day, hour, minute, second);
		else if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Time3)
			return std::format("{}-{:02}-{:02} {:02}:{:02}:{:02}.{:03}", year, month, day, hour, minute, second, millisecond);
	}
	else
	{
		auto get_ms_time = [&]()->std::time_t {
			return std::chrono::time_point_cast<std::chrono::milliseconds>(aTime).time_since_epoch().count();
		};

		std::time_t iNow = get_ms_time();
		std::time_t iSecond = (std::time_t)(iNow / 1000);
		MyUInt32 iMillisecond = (MyUInt32)(iNow % iSecond);

		std::ostringstream os;
		if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Date1)
		{
			os << std::put_time(std::localtime(&iSecond), "%Y%m%d");
		}
		else if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Time1)
		{
			os << std::put_time(std::localtime(&iSecond), "%Y%m%d_%H%M%S");
		}
		else if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Time2)
		{
			os << std::put_time(std::localtime(&iSecond), "%Y-%m-%d %H:%M:%S");
		}
		else if (aTimeFormatType == ENUM_TIME_FORMAT_TYPE::Time3)
		{
			os << std::put_time(std::localtime(&iSecond), "%Y-%m-%d %H:%M:%S");
			os << "." << std::setw(3) << std::setfill('0') << iMillisecond;
		}
		return os.str();
	}
	return std::string{};
}