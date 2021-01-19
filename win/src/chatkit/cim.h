/** @file cim.h
  * @brief sdk文件
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_
#define _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_

#include "cim_def.h"
#include "core/client.h"

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

    struct ChatKitConfig {
        std::string serverIp;								// 服务器IP地址
        uint16_t	serverGataPort = kDefaultGateSrvPort;	// Gate服务端口
        uint16_t    serverHttpPort = kDefaultHttpSrvPort;	// Http服务端口
    };

    CIM_DLL_API int initChatKit(const ChatKitConfig& config);

    const ChatKitConfig& getChatKitConfig();
}

#endif//_CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_