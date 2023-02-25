#pragma once

#include <memory>
#include <string>

namespace cmake_dap {

// in sync with cmake::LogLevel
enum class LogLevel
{
  kUndefined,
  kError,
  kWarning,
  kNotice,
  kStatus,
  kVerbose,
  kDebug,
  kTrace,
};

struct FrameLocation
{
  std::string name;
  std::string filePath;
  uint32_t line;
};

struct MessageEvent
{
  std::string message;
  LogLevel level;
};

class CMakeDapServer
{
public:
  CMakeDapServer() = default;
  CMakeDapServer(const CMakeDapServer&) = delete;

  virtual ~CMakeDapServer() = default;

  // create() constructs and returns a new Server.
  static std::unique_ptr<CMakeDapServer> create();

  virtual bool SetConnectAddress(const std::string& bindAddress) = 0;

  virtual bool Start() = 0;

  virtual void SourceReached(const FrameLocation& location) = 0;

  virtual void OnMessage(const MessageEvent& event) = 0;
};

}
