#ifndef WEATHER_PARSER_H
#define WEATHER_PARSER_H

#include <parser.h>

#include <string>
#include <variant>

#include "weather_day.h"
#include "weather_period.h"

struct WeatherParserError {
    std::string message;
};

using WeatherParseResult = std::variant<std::vector<WeatherDay>, WeatherParserError>;
using DayParseResult = std::variant<WeatherDay, WeatherParserError>;
using PeriodParseResult = std::variant<WeatherPeriod, WeatherParserError>;

class WeatherParser {
public:
    WeatherParseResult Parse(Json json);

private:
    DayParseResult Parse(std::string);
    PeriodParseResult Parse();
};

#endif  // !WEATHER_PARSER_H
