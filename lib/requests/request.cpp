#include "request.h"

#include <cpr/cpr.h>

#include <iostream>

// https://api.open-meteo.com/v1/forecast?latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16

void get_weather_by_lat_lon() {
    const char* api_key = "sNzuIBF9w5qPxUQkiPTE+g==2Z9YMhaWVzcqSXf0";

    cpr::Parameters params = {{"latitude", "59.57"}, {"longitude", "30.19"}};

    cpr::Header header = {{"X-Api-Key", api_key}};

    cpr::Response response =
        cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"}, params);

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

void get_lat_lon_by_city_name(const std::string& city_name) {
    const char* api_key = "sNzuIBF9w5qPxUQkiPTE+g==2Z9YMhaWVzcqSXf0";

    cpr::Parameters params;
    params.Add({{"name"}, city_name});

    cpr::Header header = {{"X-Api-Key", api_key}};

    cpr::Response response =
        cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"}, params, header);

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
