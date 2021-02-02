#include "pch.h"
#include "cim/cim.h"

#include <WINSOCK2.H>

#define MSGSIZE 1024

namespace cim {

    ChatKitConfig g_config;

    int initChatKit(const ChatKitConfig& config) {
        // evpp ��windows�£���Ҫ�ȳ�ʼ��socket
#ifdef _WINDOWS_
        WSADATA wsaData;
        SOCKET sListen;
        SOCKET sClient;
        SOCKADDR_IN local;
        SOCKADDR_IN client;
        char szMessage[MSGSIZE];
        int ret;
        int iaddrSize = sizeof(SOCKADDR_IN);

        if (WSAStartup(0x0202, &wsaData) != 0) {
            LogError("windows socket init error");
            return kError;
        }

#endif
        g_config = config;

        // init loop
        cim::core::Client::getInstance();

        // init db
        if (!cim::db::SqliteHelper::getInstance()->init()) {
            return kError;
        }

        return kSuccess;
    }

    CIM_DLL_API void cleanup() {
        cim::core::Client::getInstance()->logout();
    }

    CIM_DLL_API void setChatKitServerInfo(const ConfigServerInfo& info) {
        g_config.serverInfo = info;
    }

    const ChatKitConfig& cim::getChatKitConfig() {
        return g_config;
    }
}



