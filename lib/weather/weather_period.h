#ifndef WEATHER_PERIOD_H
#define WEATHER_PERIOD_H

#include <cstdint>

struct WeatherPeriod {
    double temperature;
    int64_t humidity;
    double rain;
    int64_t cloud_cover;
    double wind_speed;
};

#endif  // !WEATHER_PERIOD_H
