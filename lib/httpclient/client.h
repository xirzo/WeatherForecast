#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <cpr/cpr.h>
#include <cpr/cprtypes.h>

#include <string>

class HttpClient {
public:
    HttpClient(const std::string& base_url);

    cpr::Response Get(const std::string& endpoint,
                      const cpr::Parameters& params = cpr::Parameters(),
                      const cpr::Header header = cpr::Header());

private:
    std::string base_url_;
    cpr::Session session_;
};

#endif  // HTTPCLIENT_H
