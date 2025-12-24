// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ChronoWrapper.h
// 创建日期：2024-04-10
// 创建人：罗俊杰
// 文件说明：对chrono的封装
// $_FILEHEADER_END ***********************************************************

#ifndef CHRONO_WRAPPER_H
#define CHRONO_WRAPPER_H

#include <chrono>
#include <tuple>
#include <string>
#include "TypeDef.h"

enum class ENUM_CLOCK_TYPE : MyUInt16
{
	Default = 0,			// 默认值
	System = 1,				// system_clock
	Steady = 2,				// steady_clock
	High_Resolution = 3,	// high_resolution_clock
	File = 4,				// file_clock,文件系统中使用的文件时间,从1601年1月1日(星期二)00:00:00开始
	GPS = 5,				// gps_clock,全球定位系统时钟,从1980年1月6日(星期日)00:00:00开始,不考虑闰秒
	UTC = 6,				// utc_clock,格林威治标准时间(GMT)或Zulu时间,从1970年1月1日(星期四)00:00:00开始,考虑闰秒
	TAI = 7,				// tai_clock,国际原子时,从1958年1月1日(星期四)00:00:00开始,不考虑闰秒
};

// 输出的时间格式类型
enum class ENUM_TIME_FORMAT_TYPE : MyUInt16
{
	Date1 = 1,	// 按照字符串YYMMDD输出
	Time1 = 10,	// 按照字符串YYMMDD_HHMMSS输出
	Time2 = 11,	// 按照字符串YYYY-MM-DD HH:MM:SS输出
	Time3 = 12,	// 按照字符串YYYY-MM-DD HH:MM:SS.MS输出
};

namespace crn = std::chrono;
using system_c = crn::system_clock;
using steady_c = crn::steady_clock;
using high_resolution_c = crn::high_resolution_clock;
using file_c = crn::file_clock;
using gps_c = crn::gps_clock;
using utc_c = crn::utc_clock;
using tai_c = crn::tai_clock;

class CChronoWrapper
{
public:
	CChronoWrapper() = default;
	~CChronoWrapper() = default;

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Clock
	// 获取当前时间
	static std::time_t MS_Time(ENUM_CLOCK_TYPE aClock);
	static std::time_t S_Time(ENUM_CLOCK_TYPE aClock);
	static std::time_t M_Time(ENUM_CLOCK_TYPE aClock);
	static std::time_t H_Time(ENUM_CLOCK_TYPE aClock);
	static std::time_t D_Time(ENUM_CLOCK_TYPE aClock);

	// 系统时间转换为其它clock
	static utc_c::time_point SystemToUTC(const system_c::time_point& aTimePoint);
	static std::time_t SystemToUTC_MS(const system_c::time_point& aTimePoint);
	static std::time_t SystemToUTC_S(const system_c::time_point& aTimePoint);
	static std::time_t SystemToUTC_M(const system_c::time_point& aTimePoint);
	static std::time_t SystemToUTC_H(const system_c::time_point& aTimePoint);
	static std::time_t SystemToUTC_D(const system_c::time_point& aTimePoint);

	static file_c::time_point SystemToFile(const system_c::time_point& aTimePoint);
	static std::time_t SystemToFile_MS(const system_c::time_point& aTimePoint);
	static std::time_t SystemToFile_S(const system_c::time_point& aTimePoint);
	static std::time_t SystemToFile_M(const system_c::time_point& aTimePoint);
	static std::time_t SystemToFile_H(const system_c::time_point& aTimePoint);
	static std::time_t SystemToFile_D(const system_c::time_point& aTimePoint);

	static gps_c::time_point SystemToGPS(const system_c::time_point& aTimePoint);
	static std::time_t SystemToGPS_MS(const system_c::time_point& aTimePoint);
	static std::time_t SystemToGPS_S(const system_c::time_point& aTimePoint);
	static std::time_t SystemToGPS_M(const system_c::time_point& aTimePoint);
	static std::time_t SystemToGPS_H(const system_c::time_point& aTimePoint);
	static std::time_t SystemToGPS_D(const system_c::time_point& aTimePoint);

	static tai_c::time_point SystemToTAI(const system_c::time_point& aTimePoint);
	static std::time_t SystemToTAI_MS(const system_c::time_point& aTimePoint);
	static std::time_t SystemToTAI_S(const system_c::time_point& aTimePoint);
	static std::time_t SystemToTAI_M(const system_c::time_point& aTimePoint);
	static std::time_t SystemToTAI_H(const system_c::time_point& aTimePoint);
	static std::time_t SystemToTAI_D(const system_c::time_point& aTimePoint);

	// 其它clock转换为系统时间
	static system_c::time_point UTCToSystem(const utc_c::time_point& aTimePoint);
	static std::time_t UTCToSystem_MS(const utc_c::time_point& aTimePoint);
	static std::time_t UTCToSystem_S(const utc_c::time_point& aTimePoint);
	static std::time_t UTCToSystem_M(const utc_c::time_point& aTimePoint);
	static std::time_t UTCToSystem_H(const utc_c::time_point& aTimePoint);
	static std::time_t UTCToSystem_D(const utc_c::time_point& aTimePoint);

	static system_c::time_point FileToSystem(const file_c::time_point& aTimePoint);
	static std::time_t FileToSystem_MS(const file_c::time_point& aTimePoint);
	static std::time_t FileToSystem_S(const file_c::time_point& aTimePoint);
	static std::time_t FileToSystem_M(const file_c::time_point& aTimePoint);
	static std::time_t FileToSystem_H(const file_c::time_point& aTimePoint);
	static std::time_t FileToSystem_D(const file_c::time_point& aTimePoint);

	static system_c::time_point GPSToSystem(const gps_c::time_point& aTimePoint);
	static std::time_t GPSToSystem_MS(const gps_c::time_point& aTimePoint);
	static std::time_t GPSToSystem_S(const gps_c::time_point& aTimePoint);
	static std::time_t GPSToSystem_M(const gps_c::time_point& aTimePoint);
	static std::time_t GPSToSystem_H(const gps_c::time_point& aTimePoint);
	static std::time_t GPSToSystem_D(const gps_c::time_point& aTimePoint);

	static system_c::time_point TAIToSystem(const tai_c::time_point& aTimePoint);
	static std::time_t TAIToSystem_MS(const tai_c::time_point& aTimePoint);
	static std::time_t TAIToSystem_S(const tai_c::time_point& aTimePoint);
	static std::time_t TAIToSystem_M(const tai_c::time_point& aTimePoint);
	static std::time_t TAIToSystem_H(const tai_c::time_point& aTimePoint);
	static std::time_t TAIToSystem_D(const tai_c::time_point& aTimePoint);

	// system_clock转换为time_t
	static std::time_t SystemToTime(system_c::time_point aTimePoint);

	// time_t转换为system_clock
	static system_c::time_point TimeToSystem(std::time_t aTime);
	static system_c::time_point System_MSToSystem(std::time_t aTime);
	static system_c::time_point System_SToSystem(std::time_t aTime);
	static system_c::time_point System_MToSystem(std::time_t aTime);
	static system_c::time_point System_HToSystem(std::time_t aTime);
	static system_c::time_point System_DToSystem(std::time_t aTime);

	static system_c::time_point UTC_MSToSystem(std::time_t aTime);
	static system_c::time_point UTC_SToSystem(std::time_t aTime);
	static system_c::time_point UTC_MToSystem(std::time_t aTime);
	static system_c::time_point UTC_HToSystem(std::time_t aTime);
	static system_c::time_point UTC_DToSystem(std::time_t aTime);

	static system_c::time_point File_MSToSystem(std::time_t aTime);
	static system_c::time_point File_SToSystem(std::time_t aTime);
	static system_c::time_point File_MToSystem(std::time_t aTime);
	static system_c::time_point File_HToSystem(std::time_t aTime);
	static system_c::time_point File_DToSystem(std::time_t aTime);

	static system_c::time_point GPS_MSToSystem(std::time_t aTime);
	static system_c::time_point GPS_SToSystem(std::time_t aTime);
	static system_c::time_point GPS_MToSystem(std::time_t aTime);
	static system_c::time_point GPS_HToSystem(std::time_t aTime);
	static system_c::time_point GPS_DToSystem(std::time_t aTime);

	static system_c::time_point TAI_MSToSystem(std::time_t aTime);
	static system_c::time_point TAI_SToSystem(std::time_t aTime);
	static system_c::time_point TAI_MToSystem(std::time_t aTime);
	static system_c::time_point TAI_HToSystem(std::time_t aTime);
	static system_c::time_point TAI_DToSystem(std::time_t aTime);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Calendars
	// 日期时间转换为系统时间
	static std::tuple<bool, crn::local_time<crn::system_clock::duration>> DateTimeToSystem(uint32_t aiYear, uint32_t aiMonth, uint32_t aiDay, uint32_t aiHour = 0, uint32_t aiMinute = 0, uint32_t aiSecond = 0, uint32_t aiMillisecond = 0);

	// 系统时间转换为日期时间
	static std::tuple<bool, crn::year_month_day, crn::hh_mm_ss<crn::milliseconds>, crn::year_month_weekday> SystemToDateTime(const crn::local_time<crn::system_clock::duration>& aTimePoint);

	// 获取下一个星期几(1~7)
	static crn::local_time<crn::system_clock::duration> NextWeekDay(uint32_t aiWeek);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取时间字符串
	static std::string GetFormatTime(ENUM_TIME_FORMAT_TYPE aTimeFormatType, bool abUseZone = false, const system_c::time_point& aTime = system_c::now());
};

#endif