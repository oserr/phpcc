#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string_view>

#include "pico_http_parser.h"

using namespace phpcc;

constexpr std::string_view kSimple =
    "GET /wp-content/uploads/2010/03/hello-kitty-darth-vader-pink.jpg HTTP/1.1\r\n"
    "Host: www.kittyhell.com\r\n"
    "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; ja-JP-mac; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3 "
    "Pathtraq/0.9\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: ja,en-us;q=0.7,en;q=0.3\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 115\r\n"
    "Connection: keep-alive\r\n"
    "Cookie: wp_ozh_wsa_visits=2; wp_ozh_wsa_visit_lasttime=xxxxxxxxxx; "
    "__utma=xxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.x; "
    "__utmz=xxxxxxxxx.xxxxxxxxxx.x.x.utmccn=(referral)|utmcsr=reader.livedoor.com|utmcct=/reader/|utmcmd=referral\r\n"
    "\r\n";

constexpr std::string_view kMultipart =
    "POST /cgi-bin/qtest HTTP/1.1\r\n"
    "Host: aram\r\n"
    "User-Agent: Mozilla/5.0 Gecko/2009042316 Firefox/3.0.10\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: en-us,en;q=0.5\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 300\r\n"
    "Connection: keep-alive\r\n"
    "Referer: http://aram/~martind/banner.htm\r\n"
    "Content-Type: multipart/form-data; boundary=2a8ae6ad-f4ad-4d9a-a92c-6d217011fe0f\r\n"
    "Content-Length: 514\r\n"
    "\r\n"
    "--2a8ae6ad-f4ad-4d9a-a92c-6d217011fe0f\r\n"
    "Content-Disposition: form-data; name=datafile1; filename=r.gif\r\n"
    "Content-Type: image/gif\r\n"
    "\r\n"
    "GIF87a.............,...........D..;\r\n"
    "--2a8ae6ad-f4ad-4d9a-a92c-6d217011fe0f\r\n"
    "Content-Disposition: form-data; name=datafile2; filename=g.gif\r\n"
    "Content-Type: image/gif\r\n"
    "\r\n"
    "GIF87a.............,...........D..;\r\n"
    "--2a8ae6ad-f4ad-4d9a-a92c-6d217011fe0f\r\n"
    "Content-Disposition: form-data; name=datafile3; filename=b.gif\r\n"
    "Content-Type: image/gif\r\n"
    "\r\n"
    "GIF87a.............,...........D..;\r\n"
    "--2a8ae6ad-f4ad-4d9a-a92c-6d217011fe0f--\r\n";

int
main()
{
    PicoHttpParser parser;

    for (std::string_view request_str : {kSimple, kMultipart}) {
        auto [req, status] = parser.ParseRequest(request_str);

        switch (status) {
            case ParseStatus::Incomplete:
                std::cerr << "Request is incomplete." << std::endl;
                return 1;
            case ParseStatus::Err:
                std::cerr << "Unable to parse request." << std::endl;
                return 1;
            default:
                break;
        }

        std::cout << "All GOOD!\n";
        std::cout << "method=" << req.method << std::endl;
        std::cout << "path=" << req.path << std::endl;
        std::cout << "minor_version=" << req.minor_version << std::endl;
        std::cout << "buff_size=" << req.buffer.size() << std::endl;
        std::cout << "bytes_read=" << req.bytes_read << std::endl;
        std::cout << "num_headers=" << req.headers.size() << std::endl;

        for (const auto& [key, val] : req.headers)
            std::cout << '\t' << key << ':' << val << std::endl;
    }

    return 0;
}
