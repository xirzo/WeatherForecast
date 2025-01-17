#ifndef FORECAST_FACTORY_H
#define FORECAST_FACTORY_H

#include <parser.h>

#include <variant>

#include "client.h"
#include "configuration.h"
#include "forecast.h"

struct ForecastCreateError {
    std::string message;
};

using ForecastCreateResult = std::variant<Forecast, ForecastCreateError>;

class ForecastFactory {
public:
    ForecastFactory(Configuration configuration);

    ForecastCreateResult Create();

private:
    JsonParser parser_;
    Configuration configuration_;
    HttpClient client_;
};

#endif  // !FORECAST_FACTORY_H
