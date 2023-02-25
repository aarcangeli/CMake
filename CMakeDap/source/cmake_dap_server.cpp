#include "cmake_dap/cmake_dap_server.h"

#include <iostream>

#include "dap/network.h"
#include "dap/session.h"

using namespace cmake_dap;

class CMakeDapServerImpl : public CMakeDapServer
{
public:
  bool SetConnectAddress(const std::string& bindAddress) override
  {
    if (ParseAddress(bindAddress)) {
      mode_ = DebugMode::kConnect;
      return true;
    }
    return false;
  }

  bool Start() override
  {
    auto session = dap::Session::create();

    if (mode_ == DebugMode::kConnect) {
      // temp
      return true;
      std::cout << "Connecting debugger to " << address_ << ":" << port_
                << std::endl;
      auto connection = dap::net::connect(address_.c_str(), port_);
      if (!connection) {
        return false;
      }
      session->bind(connection);
      session_ = std::move(session);
    } else {
      return false;
    }

    // todo: wait execute

    return true;
  }
  void SourceReached(const FrameLocation& location) override
  {
    //
    int t = 0;
  }
  void OnMessage(const MessageEvent& event) override
  {
    //
    int t = 0;
  }

private:
  enum class DebugMode
  {
    kNone,
    kConnect,
    kListen,
  };

  DebugMode mode_ = DebugMode::kNone;
  std::string address_;
  uint32_t port_;

  std::unique_ptr<dap::Session> session_;

  bool ParseAddress(const std::string& bindAddress)
  {
    std::string address;
    std::string port;

    size_t colon = bindAddress.find(':');
    if (colon != std::string::npos) {
      address = bindAddress.substr(0, colon);
      port = bindAddress.substr(colon + 1);
    } else {
      address = "localhost";
      port = bindAddress;
    }

    // Parse port number
    char* endPtr;
    uint32_t portNumber = strtoul(port.c_str(), &endPtr, 0);
    if (*endPtr != '\0' || portNumber >= 65536) {
      return false;
    }

    address_ = address;
    port_ = portNumber;
    return true;
  }
};

std::unique_ptr<CMakeDapServer> CMakeDapServer::create()
{
  return std::make_unique<CMakeDapServerImpl>();
}
