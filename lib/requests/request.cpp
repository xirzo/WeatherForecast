#include "request.h"

#include <cpr/cpr.h>

#include <iostream>

void request() {
    const char* api_key = "sNzuIBF9w5qPxUQkiPTE+g==2Z9YMhaWVzcqSXf0";

    cpr::Parameters params = {{"lat", "59.57"}, {"lon", "30.19"}};

    cpr::Header header = {{"X-Api-Key", api_key}};

    cpr::Response response =
        cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/weather"}, header, params);

    if (response.error) {
        std::cerr << "Request Error: " << response.error.message << std::endl;
        return;
    }

    if (response.status_code != 200) {
        std::cerr << "API Error: " << response.text << std::endl;
        return;
    }

    std::cout << response.text << std::endl;
}
