#ifndef FORECAST_FACTORY_H
#define FORECAST_FACTORY_H

#include <parser.h>

#include <variant>
#include <vector>

#include "client.h"
#include "configuration.h"
#include "forecast.h"
#include "weather_parser.h"

struct ForecastCreateError {
    std::string message;
};

using ForecastCreateResult = std::variant<std::vector<Forecast>, ForecastCreateError>;

class ForecastFactory {
public:
    ForecastFactory(Configuration configuration);

    ForecastCreateResult Create();

private:
    WeatherParser weather_parser_;
    JsonParser json_parser_;
    Configuration configuration_;
    HttpClient client_;

    std::string JoinArrayToString(const std::vector<std::string>& array);
};

#endif  // !FORECAST_FACTORY_H
