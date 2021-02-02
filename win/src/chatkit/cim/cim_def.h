/** @file cim_def.h
  * @brief cim_def
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_
#define _CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_

#include <cstdint>
#include <string>

const uint16_t kProtocolVersion = 1;

// MessageLite, evpp::Buffer
#define PARSE_PB_AND_CHECK(rsp,buffer) if (!rsp.ParseFromArray(buffer->data(), buffer->length())) { \
LogInfo("prase pb error."); \
return; \
} else { \
    buffer->Skip(rsp.ByteSize()); \
} \


namespace cim {
    enum Result {
        kUnknown = 0,
        kSuccess = 1,
        kError = -1,

        // more
    };

    // total 16 Bytes
    struct IMHeader {
        uint32_t len;		// 数据部长度
        uint16_t version;   // 协议版本号
        uint16_t flag;		// 预留
        uint16_t service_id;// 预留
        uint16_t cmd;		// 消息ID
        uint16_t seq;		// 包序号
        uint16_t reserved;  // 保留位
    };

    const uint16_t kDefaultGateSrvPort = 8000;
    const uint16_t kDefaultHttpSrvPort = 18080;

    const std::wstring kDefaultAppDataDir = L"data";
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
}

#endif//_CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_