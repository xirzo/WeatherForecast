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
    WeatherParseResult Parse(Json& json);

private:
    DayParseResult ParseDay(JsonObject& hourly, size_t start_index);
    PeriodParseResult ParsePeriod(const JsonArray& temperatureArray,
                                  const JsonArray& humidityArray,
                                  const JsonArray& rainArray,
                                  const JsonArray& cloudCoverArray,
                                  const JsonArray& windSpeedArray, size_t index);
};

#endif  // !WEATHER_PARSER_H
