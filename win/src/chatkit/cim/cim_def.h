/** @file cim_def.h
  * @brief cim_def
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_
#define _CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_

#include <cstdint>
#include <string>

#include "cim/pb/CIM.Def.pb.h"
#include "cim/cim_dll.h"
using namespace CIM::Def;

const uint16_t kProtocolVersion = 1;

// MessageLite, evpp::Buffer
#define PARSE_PB_AND_CHECK(rsp,buffer) if (!rsp.ParseFromArray(buffer->data(), buffer->length())) { \
LogInfo("prase pb error."); \
return; \
} else { \
    buffer->Skip(rsp.ByteSize()); \
} \

namespace cim {

#ifndef byte_t
#define byte_t char
#endif

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

    struct MessageModel {
      public:
        std::string client_msg_id; // 客户端消息ID（UUID）
        uint64_t server_msg_id; // 服务端消息ID

        CIMResCode msg_res_code;     // 消息错误码
        CIMMsgFeature msg_feature;   // 消息属性
        CIMSessionType session_type; // 会话类型
        uint64_t from_user_id;         // 来源会话ID
        uint64_t to_session_id;        // 目标会话ID
        uint32_t create_time;          // 消息创建时间戳（毫秒）

        CIMMsgType msg_type;      // 消息类型
        CIMMsgStatus msg_status; // 消息状态（预留）
        std::string msg_data;          // 消息内容
        /*optional*/
        std::string attach;                    // 消息附件（预留）
        CIMClientType sender_client_type; // 发送者客户端类型

      public:
        CIM_DLL_API MessageModel();
        CIM_DLL_API MessageModel(const CIM::Def::CIMMsgInfo& info);

        /** @fn IsMyMsg
          * @brief 是否属于自己发送的消息
          * @return 结果
          */
        CIM_DLL_API bool IsMyMsg() const;

        /** @fn IsSystemMsg
          * @brief 是否属于系统消息
          * @return 结果
          */
        CIM_DLL_API bool IsSystemMsg() const;
    };
}

#endif//_CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_