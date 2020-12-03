#include "event_loop.h"
#include "base/Log.h"
#include <thread>

cim::core::EventLoop::EventLoop() {
    io_context_ = new asio::io_context();

    std::thread t([this]() {
        LogInfo("io_context run...");
        this->io_context_->run();
        LogInfo("io_context exit...");
    });
    t.detach();
}

asio::io_context &cim::core::EventLoop::getLoop() {
    return *io_context_;
}
