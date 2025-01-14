#ifndef FORECAST_FACTORY_H
#define FORECAST_FACTORY_H

#include "configuration.h"
#include "forecast.h"

class ForecastFactory {
public:
    ForecastFactory(Configuration configuration);

    Forecast Create();

private:
    Configuration configuration_;
};

#endif  // !FORECAST_FACTORY_H
