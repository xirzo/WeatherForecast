#include "forecast_factory.h"

#include <string>
#include <variant>

#include "parser.h"
#include "weather_parser.h"

ForecastFactory::ForecastFactory(Configuration configuration)
    : configuration_(configuration),
      client_("https://api.open-meteo.com/v1"),
      json_parser_(),
      weather_parser_() {}

std::string ForecastFactory::JoinArrayToString(const std::vector<std::string>& array) {
    std::ostringstream oss;

    for (size_t i = 0; i < array.size(); ++i) {
        oss << array[i];
        if (i != array.size() - 1) {
            oss << ",";
        }
    }

    return oss.str();
}

ForecastCreateResult ForecastFactory::Create() {
    std::vector<Forecast> forecasts;

    for (size_t i = 0; i < configuration_.cities.size(); ++i) {
        cpr::Parameters params;

        std::vector<std::string> hourly = {"temperature_2m", "relative_humidity_2m",
                                           "rain", "cloud_cover", "wind_speed_10m"};

        std::string hourly_str = JoinArrayToString(hourly);

        params.Add({"latitude", std::to_string(configuration_.cities[i].latitude)});
        params.Add({"longitude", std::to_string(configuration_.cities[i].longitude)});
        params.Add({"forecast_days", std::to_string(configuration_.days)});
        params.Add({"hourly", hourly_str});
        params.Add({"daily", "weather_code"});

        cpr::Response response =
            cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"}, params);

        if (response.error) {
            return ForecastCreateError{response.error.message};
        }

        ParseResult parse_result = json_parser_.Parse(response.text);

        if (std::holds_alternative<ParserError>(parse_result)) {
            return ForecastCreateError{std::get<ParserError>(parse_result).message};
        }

        Json json = std::get<Json>(parse_result);

        WeatherParseResult forecast_result = weather_parser_.Parse(json);

        if (std::holds_alternative<WeatherParserError>(forecast_result)) {
            return ForecastCreateError{
                std::get<WeatherParserError>(forecast_result).message};
        }

        forecasts.push_back(std::get<Forecast>(forecast_result));
    }

    return forecasts;
}
