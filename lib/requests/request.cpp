#include "request.h"

#include <cpr/cpr.h>

#include <iostream>

void request() {
    cpr::Response response =
        cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                 cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                 cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    std::cout << response.status_code << std::endl;
    std::cout << response.header["content-type"] << std::endl;
    std::cout << response.text << std::endl;
}
