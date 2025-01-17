#ifndef WEATHER_DAY_H
#define WEATHER_DAY_H

#include <string>

#include "weather_period.h"

struct WeatherDay {
    std::string date;

    WeatherPeriod morning;
    WeatherPeriod afternoon;
    WeatherPeriod evening;
    WeatherPeriod night;
};

#endif  // !WEATHER_DAY_H
