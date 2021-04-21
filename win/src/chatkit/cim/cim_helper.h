#ifndef _CIM_HELPER_B836EAC6_9A7C_4763_A032_D3B9371E50E7_
#define _CIM_HELPER_B836EAC6_9A7C_4763_A032_D3B9371E50E7_

#include "cim/cim_dll.h"
#include "cim/cim_def.h"

namespace cim {
    /** @fn initChatKit
    * @brief ��ʼ��SDK
    * @param ������Ϣ
    * @return cim::Result
    */
    CIM_DLL_API int initChatKit(const ChatKitConfig& config);
    /** @fn cleanup
      * @brief �˳�ǰ�ͷ������Դ
      */
    CIM_DLL_API void cleanup();

    /** @fn setChatKitServerInfo
      * @brief ���÷�������Ϣ
      * @param IP�Ͷ˿���Ϣ
      */
    CIM_DLL_API void setChatKitServerInfo(const ConfigServerInfo& info);

    /** @fn getChatKitConfig
      * @brief ��ȡ������Ϣ
      * @return
      */
    const ChatKitConfig& getChatKitConfig();
}

#endif//_CIM_HELPER_B836EAC6_9A7C_4763_A032_D3B9371E50E7_