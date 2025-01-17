#ifndef WEATHER_PARSER_H
#define WEATHER_PARSER_H

#include <parser.h>

#include <string>
#include <variant>

#include "forecast.h"

struct WeatherParserError {
    std::string message;
};

using WeatherParseResult = std::variant<Forecast, WeatherParserError>;

class WeatherParser {
public:
    WeatherParseResult Parse(Json json);

private:
};

#endif  // !WEATHER_PARSER_H
