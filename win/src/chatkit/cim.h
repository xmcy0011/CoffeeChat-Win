/** @file cim.h
  * @brief sdk文件
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_
#define _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_

#include "cim_def.h"
#include "core/client.h"
#include "base/Log.h"

// protobuf
#include "pb/CIM.Def.pb.h"
#include "pb/CIM.Login.pb.h"
#include "pb/CIM.List.pb.h"
#include "pb/CIM.Message.pb.h"
#include "pb/CIM.Group.pb.h"
#include "pb/CIM.Voip.pb.h"

// 导出类
#include "cim_dll.h"

namespace cim {
    const uint16_t kDefaultGateSrvPort = 8000;
    const uint16_t kDefaultHttpSrvPort = 18080;

    const std::wstring kDefaultAppDataDir = L"";
    const std::wstring kDefaultAppDataFilename = L"msg.db";

    struct ConfigServerInfo {
        std::string ip;								// 服务器IP地址
        uint16_t	gatePort = kDefaultGateSrvPort;	// Gate服务端口
        uint16_t    httpPort = kDefaultHttpSrvPort;	// Http服务端口
    };

    struct AppConfig {
        std::wstring app_data_dir = kDefaultAppDataDir; // 存储目录
    };

    struct ChatKitConfig {
        ConfigServerInfo	serverInfo; // set by setChatKitServerInfo() or initChatKit()
        AppConfig			appConfig;
    };

    /** @fn initChatKit
      * @brief 初始化SDK
      * @param 配置信息
      * @return cim::Result
      */
    CIM_DLL_API int initChatKit(const ChatKitConfig& config);

    /** @fn setChatKitServerInfo
      * @brief 设置服务器信息
      * @param IP和端口信息
      */
    CIM_DLL_API void setChatKitServerInfo(const ConfigServerInfo& info);

    const ChatKitConfig& getChatKitConfig();
}

#endif//_CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_