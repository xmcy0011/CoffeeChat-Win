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

    struct MessageModel {
      public:
        std::string client_msg_id; // �ͻ�����ϢID��UUID��
        uint64_t server_msg_id; // �������ϢID

        CIMResCode msg_res_code;     // ��Ϣ������
        CIMMsgFeature msg_feature;   // ��Ϣ����
        CIMSessionType session_type; // �Ự����
        uint64_t from_user_id;         // ��Դ�ỰID
        uint64_t to_session_id;        // Ŀ��ỰID
        uint32_t create_time;          // ��Ϣ����ʱ��������룩

        CIMMsgType msg_type;      // ��Ϣ����
        CIMMsgStatus msg_status; // ��Ϣ״̬��Ԥ����
        std::string msg_data;          // ��Ϣ����
        /*optional*/
        std::string attach;                    // ��Ϣ������Ԥ����
        CIMClientType sender_client_type; // �����߿ͻ�������

      public:
        CIM_DLL_API MessageModel();
        CIM_DLL_API MessageModel(const CIM::Def::CIMMsgInfo& info);

        /** @fn IsMyMsg
          * @brief �Ƿ������Լ����͵���Ϣ
          * @return ���
          */
        CIM_DLL_API bool IsMyMsg() const;

        /** @fn IsSystemMsg
          * @brief �Ƿ�����ϵͳ��Ϣ
          * @return ���
          */
        CIM_DLL_API bool IsSystemMsg() const;
    };
}

#endif//_CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_