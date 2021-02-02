/** @file cim_conn_base.h
  * @brief cim_conn_base
  * @author fei.xu
  * @date 2020/8/24
  */

#ifndef _CIM_CONN_BASE_E3284850_C63B_415E_8437_DA08266183CB_
#define _CIM_CONN_BASE_E3284850_C63B_415E_8437_DA08266183CB_

#include "cim/pb/CIM.Def.pb.h"
#include <memory>
#include <string>

namespace cim {
    using namespace std;

    enum ConnectStatus {
        kDefault,
        kConnectting,
        kConnectOk,
        kDisConnect
    };

    // 状态改变回调接口
    struct IConnectStatus {
        virtual void onConnected(const string& ip, const uint16_t& port) = 0;
        virtual void onDisconnect(string error) = 0;
    };

    // 数据回调
    struct IClientConnDelegateData {
        virtual void onHandle(const char* data, const int& len) = 0;
    };

    // 与服务器通信的一个连接
    struct IClientConn {
        virtual void connect(string ip, uint16_t port) = 0;
        virtual void disconnect() = 0;
        virtual ConnectStatus connStatus() = 0;

        virtual int sendRaw(const char* data, const int& len) = 0;
        virtual int send(CIM::Def::CIMCmdID cmd_id, const char* data, const int& len) = 0;
        virtual int sendRequest() = 0;
    };

}

#endif//_CIM_CONN_BASE_E3284850_C63B_415E_8437_DA08266183CB_