/** @file cim.h
  * @brief sdk�ļ�
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

// ������
#include "cim_dll.h"

namespace cim {
    struct ChatKitConfig {

    };

    int initChatKit(const ChatKitConfig& config);
}

#endif//_CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_