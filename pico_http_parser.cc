#include "pico_http_parser.h"

#include <string_view>

#include "pico_http_request.h"
#include "picohttpparser.h"

namespace phpcc {

PicoHttpRequest
PicoHttpParser::ParseRequest(std::string_view req_buff, size_t last_len) const {
    const char *method;
    size_t method_len;
    const char *path;
    size_t path_len;
    int minor_version;
    size_t num_headers = max_headers_;
    phr_header headers[max_headers_];

    int ret = phr_parse_request(
            req_buff.data(),
            req_buff.size(),
            &method,
            &method_len,
            &path,
            &path_len,
            &minor_version,
            headers,
            &num_headers,
            last_len);

    if (ret == -1)
        throw std::domain_error("Unable to parse request.");

    if (ret == -2)
        throw std::underflow_error("Request is incomplete.");

    PicoHttpRequest req;
    req.buffer = req_buff;
    req.method = std::string_view(method, method_len);
    req.path = std::string_view(path, path_len);
    req.minor_version = minor_version;
    req.bytes_read = ret;

    for (size_t i = 0; i < num_headers; ++i) {
        const auto& h = headers[i];
        std::string_view header_name(h.name, h.name_len);
        std::string_view header_value(h.value, h.value_len);
        req.headers.emplace(header_name, header_value);
    }

    return req;
}

} // namespace phpcc
