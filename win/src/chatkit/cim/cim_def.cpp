#include "pch.h"
#include "cim_def.h"
#include "cim/core/client.h"

namespace cim {
    MessageModel::MessageModel():
        server_msg_id(0),
        msg_res_code(CIM::Def::kCIM_RES_CODE_UNKNOWN),
        msg_feature(CIM::Def::kCIM_MSG_FEATURE_DEFAULT),
        session_type(CIM::Def::kCIM_SESSION_TYPE_Invalid),
        from_user_id(0), to_session_id(0), create_time(0),
        msg_type(CIM::Def::kCIM_MSG_TYPE_UNKNOWN),
        msg_status(CIM::Def::kCIM_MSG_STATUS_NONE),
        sender_client_type(CIM::Def::kCIM_CLIENT_TYPE_DEFAULT) {
    }
    MessageModel::MessageModel(const CIM::Def::CIMMsgInfo& info) {
        client_msg_id = info.client_msg_id();
        server_msg_id = info.server_msg_id();

        msg_res_code = info.msg_res_code();
        msg_feature = info.msg_feature();

        session_type = info.session_type();
        from_user_id = info.from_user_id();
        to_session_id = info.msg_res_code();
        create_time = info.create_time();
        msg_type = info.msg_type();
        msg_status = info.msg_status();

        attach = info.attach();
        sender_client_type = info.sender_client_type();

        msg_data = info.msg_data();
    }

    bool MessageModel::IsMyMsg() const {
        return from_user_id == cim::core::Client::getInstance()->GetUserId();
    }

    bool MessageModel::IsSystemMsg() const {
        return msg_type == kCIM_MSG_TYPE_TIPS || msg_type == kCIM_MSG_TYPE_NOTIFACATION;
    }

}