#include "weather_parser.h"

#include <parser.h>

#include <iostream>
#include <string>
#include <variant>

#include "weather_day.h"
#include "weather_period.h"

WeatherParseResult WeatherParser::Parse(Json json) {
    std::vector<WeatherDay> days;

    if (std::holds_alternative<JsonObject>(json.at("hourly")) == false) {
        return WeatherParserError("Hourly json object was not parsed");
    }

    JsonObject hourly = std::get<JsonObject>(json.at("hourly"));

    if (std::holds_alternative<JsonArray>(hourly.at("time")) == false) {
        return WeatherParserError("Time json array was not parsed");
    }

    JsonArray time = std::get<JsonArray>(hourly["time"]);

    uint64_t number_of_days = time.size() / static_cast<size_t>(24);

    std::cout << number_of_days << std::endl;

    return days;
}

DayParseResult WeatherParser::Parse(std::string a) {
    WeatherDay day;

    return day;
}

PeriodParseResult WeatherParser::Parse() {
    WeatherPeriod period;

    return period;
}
