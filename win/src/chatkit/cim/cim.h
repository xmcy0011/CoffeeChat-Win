/** @file cim.h
  * @brief sdkÎÄ¼þ
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_
#define _CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_

// dll
#include "cim/cim_def.h"
#include "cim/cim_helper.h"
#include "cim/cim_dll.h"

// base
#include "cim/base/Log.h"
#include "cim/base/noncopyable.h"
#include "cim/base/Exception.h"

// core
#include "cim/core/callback.h"
#include "cim/core/cim_conn_base.h"
#include "cim/core/client.h"
#include "cim/core/user_manager.h"
#include "cim/core/chat_manager.h"

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

#endif//_CIM_5CC209E1_C52B_43B1_9339_2A2145CADB60_