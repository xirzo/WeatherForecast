#include "client.h"

HttpClient::HttpClient(const std::string& base_url) {
    base_url_ = base_url;
    session_.SetUrl(base_url);
}

cpr::Response HttpClient::Get(const std::string& endpoint, const cpr::Parameters& params,
                              const cpr::Header header) {
    session_.SetUrl(base_url_ + endpoint);
    session_.SetParameters(params);
    session_.SetHeader(header);
    return session_.Get();
}
