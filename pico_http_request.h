#pragma once

#include <optional>
#include <string_view>
#include <unordered_map>

namespace phpcc {

struct PicoHttpRequest {
  std::string_view buffer;
  std::string_view method;
  std::string_view path;
  int minor_version;
  int bytes_read;
  std::unordered_multimap<std::string_view, std::string_view> headers;
};

} // namespace phpcc
