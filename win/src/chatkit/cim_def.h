/** @file cim_def.h
  * @brief cim_def
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_
#define _CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_

#include <cstdint>

const int kSuccess = 0;
const int kError = -1;

namespace cim {
    enum Result {
        kUnknown = 0,
        kSuccess = 1,
        kError = -1,

        // more
    };
}

const uint16_t kProtocolVersion = 1;

// MessageLite, evpp::Buffer
#define PARSE_PB_AND_CHECK(rsp,buffer) if (!rsp.ParseFromArray(buffer->data(), buffer->length())) { \
LogInfo("prase pb error."); \
return; \
} else { \
    buffer->Skip(rsp.ByteSize()); \
} \

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

#endif//_CIM_DEF_B47F9BFC_8296_4772_81A8_D8A11896EC2F_