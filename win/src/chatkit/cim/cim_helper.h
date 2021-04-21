#ifndef _CIM_HELPER_B836EAC6_9A7C_4763_A032_D3B9371E50E7_
#define _CIM_HELPER_B836EAC6_9A7C_4763_A032_D3B9371E50E7_

#include "cim/cim_dll.h"
#include "cim/cim_def.h"

namespace cim {
    /** @fn initChatKit
    * @brief 初始化SDK
    * @param 配置信息
    * @return cim::Result
    */
    CIM_DLL_API int initChatKit(const ChatKitConfig& config);
    /** @fn cleanup
      * @brief 退出前释放相关资源
      */
    CIM_DLL_API void cleanup();

    /** @fn setChatKitServerInfo
      * @brief 设置服务器信息
      * @param IP和端口信息
      */
    CIM_DLL_API void setChatKitServerInfo(const ConfigServerInfo& info);

    /** @fn getChatKitConfig
      * @brief 获取配置信息
      * @return
      */
    const ChatKitConfig& getChatKitConfig();
}

#endif//_CIM_HELPER_B836EAC6_9A7C_4763_A032_D3B9371E50E7_