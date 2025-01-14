#include "client.h"

HttpClient::HttpClient(const std::string& base_url) {
    session_.SetUrl(base_url);
}

cpr::Response HttpClient::Get(const std::string& endpoint,
                              const cpr::Parameters& params) {
    session_.SetUrl(base_url_ + endpoint);
    session_.SetParameters(params);
    return session_.Get();
}
