// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：CommonMacro.h
// 创建日期：2014-12-05
// 创建人：罗俊杰
// 文件说明：通用宏定义
// $_FILEHEADER_END ***********************************************************

#ifndef COMMON_MACRO_H
#define COMMON_MACRO_H

#include "TypeDef.h"

// 路径长度
constexpr MyUInt16 DEF_MAX_PATH = 260;
// 版本长度
constexpr MyUInt32 DEF_VERSION_LEN = 32;
// IP地址长度
constexpr MyUInt16 DEF_IP_ADDR_LEN = 16;
// MTU分包大小
constexpr MyUInt32 DEF_MTU_SIZE = 1440;
// 字节单元大小
constexpr MyUInt32 DEF_UNIT_BYTE_SIZE = 4;
// Svr端接收缓存大小
constexpr MyUInt32 DEF_SVR_RECV_BUFF_LEN = 512;

// 模块名
constexpr char BaseCodecMod[] = "BaseCodec";
constexpr char CharsetMod[] = "Charset";
constexpr char CurlMod[] = "Curl";
constexpr char DBMod[] = "DB_Common";
constexpr char DBMod_MySQL[] = "DB_MySQL";
constexpr char DBMod_ODBC[] = "DB_ODBC";
constexpr char EncryptMod[] = "Encrypt";
constexpr char EventMod[] = "Event";
constexpr char ExceptionMod[] = "Exception";
constexpr char FileMod_Ini[] = "IniFile";
constexpr char JsonMod_Rapid[] = "Json_Rapid";
constexpr char HashMod[] = "Hash";
constexpr char MemoryMod_Buffer[] = "AutoFreeBuffer";
constexpr char MongoMod[] = "Mongo";
constexpr char NetMod[] = "Net_Common";
constexpr char NetMod_Client[] = "Network_Client";
constexpr char NetMod_Server[] = "Network_Server";
constexpr char NetMod_Epoll[] = "Network_Epoll";
constexpr char NetMod_IOCP[] = "Network_IOCP";
constexpr char NetMod_Pack[] = "PackDeal";
constexpr char NetMod_RawSocket[] = "RawSocket";
constexpr char ProtobufMod[] = "Protobuf";
constexpr char QueueMod_Recycling[] = "RecyclingObjectPool";
constexpr char RandomMod[] = "Random";
constexpr char RedisMod[] = "Redis";
constexpr char SerializationMod[] = "Serialization";
constexpr char SystemMod[] = "System";
constexpr char SystemMod_Linux[] = "System_Linux";
constexpr char SystemMod_Windows[] = "System_Windows";
constexpr char ThreadMod[] = "Thread";
constexpr char TimerMod[] = "Timer";
constexpr char UtilsMod_Addr[] = "AddrUtils";
constexpr char UtilsMod_String[] = "StringUtils";
constexpr char VersionMod[] = "Version";

constexpr char MediaMod[] = "Media_Common";
constexpr char MediaMod_File[] = "Media_File";
constexpr char MediaMod_Rtmp[] = "Media_Rtmp";
constexpr char MediaMod_Rtp[] = "Media_Rtp";

constexpr char MediaPCMod[] = "Media_PC";
constexpr char MediaPCMod_Capture[] = "Media_PC_Capture";
constexpr char MediaPCMod_Decode[] = "Media_PC_Decode";
constexpr char MediaPCMod_Encode[] = "Media_PC_Encode";
constexpr char MediaPCMod_LogicDeal[] = "Media_PC_LogicDeal";
constexpr char MediaPCMod_MediaDeal[] = "Media_PC_MediaDeal";
constexpr char MediaPCMod_Synchronization[] = "Media_PC_Synchronization";
constexpr char MediaPCMod_NetworkDeal[] = "Media_PC_NetworkDeal";
constexpr char MediaPCMod_Play[] = "Media_PC_Play";
constexpr char MediaPCMod_Screenshots[] = "Media_PC_Screenshots";

#endif