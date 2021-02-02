/** @file cim.h
  * @brief sdk文件
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_
#define _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_

// dll
#include "cim/cim_def.h"
#include "cim_dll.h"

// base
#include "cim/base/Log.h"
#include "cim/base/noncopyable.h"
#include "cim/base/Exception.h"

// core
#include "cim/core/callback.h"
#include "cim/core/cim_conn_base.h"
#include "cim/core/client.h"
#include "cim/core/user_manager.h"

// protobuf
#include "cim/pb/CIM.Def.pb.h"
#include "cim/pb/CIM.Login.pb.h"
#include "cim/pb/CIM.List.pb.h"
#include "cim/pb/CIM.Message.pb.h"
#include "cim/pb/CIM.Group.pb.h"
#include "cim/pb/CIM.Voip.pb.h"

// db
#include "cim/db/config_dao.h"
#include "cim/db/sqlite3_helper.h"

namespace cim {
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

    /** @fn getChatKitConfig
      * @brief 获取配置信息
      * @return
      */
    const ChatKitConfig& getChatKitConfig();
}

#endif//_CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_