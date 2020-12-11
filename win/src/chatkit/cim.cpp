#include "cim.h"

#include <WINSOCK2.H>

#define MSGSIZE 1024

int cim::initChatKit(const ChatKitConfig& config) {

    // evpp 再windows下，需要先初始化socket

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
        return kError;
    }

    return kSuccess;
#endif
}
