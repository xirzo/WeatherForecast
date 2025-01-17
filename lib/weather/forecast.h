#ifndef FORECAST_H
#define FORECAST_H

#include <string>
#include <vector>

#include "weather_day.h"

struct Forecast {
    std::string city_name;
    std::vector<WeatherDay> days;
};

#endif  // !FORECAST_H
