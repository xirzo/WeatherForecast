#include "forecast_factory.h"

#include <iostream>
#include <string>

#include "parser.h"
#include "weather_day.h"

ForecastFactory::ForecastFactory(Configuration configuration)
    : configuration_(configuration),
      client_("https://api.open-meteo.com/v1"),
      parser_() {}

ForecastCreateResult ForecastFactory::Create() {
    Forecast forecast;

    for (size_t i = 0; i < configuration_.cities.size(); ++i) {
        cpr::Parameters params;

        params.Add({"latitude", std::to_string(configuration_.cities[i].latitude)});
        params.Add({"longitude", std::to_string(configuration_.cities[i].longitude)});
        params.Add({"forecast_days", std::to_string(configuration_.days)});

        cpr::Response response =
            cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"}, params);

        if (response.error) {
            return ForecastCreateError{response.error.message};
        }

        std::cout << response.text << std::endl;

        ParseResult parse_result = parser_.Parse(response.text);

        if (std::holds_alternative<ParserError>(parse_result)) {
            return ForecastCreateError{std::get<ParserError>(parse_result).message};
        }

        Json json = std::get<Json>(parse_result);

        WeatherDay weather_day;

        forecast.push_back(weather_day);
    }

    return forecast;
}
