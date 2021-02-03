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
        uint32_t len;		// ���ݲ�����
        uint16_t version;   // Э��汾��
        uint16_t flag;		// Ԥ��
        uint16_t service_id;// Ԥ��
        uint16_t cmd;		// ��ϢID
        uint16_t seq;		// �����
        uint16_t reserved;  // ����λ
    };

    const uint16_t kDefaultGateSrvPort = 8000;
    const uint16_t kDefaultHttpSrvPort = 18080;

    const std::wstring kDefaultAppDataDir = L"data";
    const std::wstring kDefaultAppDataFilename = L"msg.db";

    struct ConfigServerInfo {
        std::string ip;								// ������IP��ַ
        uint16_t	gatePort = kDefaultGateSrvPort;	// Gate����˿�
        uint16_t    httpPort = kDefaultHttpSrvPort;	// Http����˿�
    };

    struct AppConfig {
        std::wstring app_data_dir = kDefaultAppDataDir; // �洢Ŀ¼
    };

    struct ChatKitConfig {
        ConfigServerInfo	serverInfo; // set by setChatKitServerInfo() or initChatKit()
        AppConfig			appConfig;
    };
}

#endif//_CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_