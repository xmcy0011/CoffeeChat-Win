#include <iostream>

//#include <WinSock2.h>
#include <thread>

#include "cim.h"
#include "base/Log.h"
#include "asio.hpp"

int main() {
//    std::cout << "hello" << std::endl;
    std::string ip = "10.0.106.117";
//    union {
//        asio::detail::socket_addr_type base;
//        asio::detail::sockaddr_storage_type storage;
//        asio::detail::sockaddr_in4_type v4;
//        asio::detail::sockaddr_in6_type v6;
//    } address;
//    ::memset(&address, 0, sizeof(address));
//
//    int address_length = sizeof(asio::detail::sockaddr_storage_type);
//    int num_wide_chars = static_cast<int>(strlen(ip.c_str())) + 1;
//    LPWSTR wide_buffer = (LPWSTR)_alloca(num_wide_chars * sizeof(WCHAR));
//    ::MultiByteToWideChar(CP_ACP, 0, ip.c_str(), -1, wide_buffer, num_wide_chars);
//    int result = ::WSAStringToAddressW(wide_buffer, 2, 0, &address.base, &address_length);

    //cim::core::EventLoop loop;
    cim::core::TcpClient client;
    client.connect(ip, 8000);

//    asio::io_context io_context;
//    asio::error_code ec;
//    asio::ip::address_v4 ipv4_address = asio::ip::make_address_v4(ip, ec);
//    asio::ip::tcp::endpoint ep(asio::ip::address(ipv4_address)/*asio::ip::address::from_string(ip)*/, 8000);
//
//    asio::ip::tcp::socket socket(io_context);
//    std::thread t([&io_context]() {
//        LogInfo("io_context run...");
//        io_context.run();
//        LogInfo("io_context exit...");
//    });
//    t.detach();
//
//    LogInfo("connecting...");
//    socket.connect(ep, ec);
//    if (ec) {
//        LogWarn(ec.message());
//    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}