#pragma once

#include <stdexcept>
#include <utility>

#include "pico_http_request.h"

namespace phpcc {

enum class ParseStatus {
    Ok,
    Err,
    Incomplete
};

class PicoHttpParser {
public:
    explicit PicoHttpParser(size_t max_headers)
      : max_headers_(max_headers)
    {
        if (max_headers == 0)
            throw std::invalid_argument("max_headers canno be zero.");
    }

    PicoHttpParser() = default;
    PicoHttpParser(const PicoHttpParser& parser) = default;
    PicoHttpParser(PicoHttpParser&& parser) = default;

    PicoHttpParser&
    operator=(const PicoHttpParser& parser) = default;

    PicoHttpParser&
    operator=(PicoHttpParser&& parser) = default;

    std::pair<PicoHttpRequest, ParseStatus>
    ParseRequest(std::string_view req_buff, size_t last_len = 0) const noexcept;

private:
    size_t max_headers_ = 512;
};

} // namespace phpcc
