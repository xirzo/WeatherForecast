#include "weather_parser.h"

#include <parser.h>

#include <string>
#include <variant>

#include "weather_day.h"
#include "weather_period.h"

WeatherParseResult WeatherParser::Parse(Json& json) {
    std::vector<WeatherDay> days;

    if (std::holds_alternative<JsonObject>(json.at("hourly")) == false) {
        return WeatherParserError("Hourly json object was not parsed");
    }

    JsonObject hourly = std::get<JsonObject>(json.at("hourly"));

    if (std::holds_alternative<JsonArray>(hourly.at("time")) == false) {
        return WeatherParserError("Time json array was not parsed");
    }

    JsonArray time = std::get<JsonArray>(hourly.at("time"));

    uint64_t number_of_days = time.size() / static_cast<size_t>(24);

    for (size_t i = 0; i < number_of_days; ++i) {
        size_t start_index = i * 24;
        DayParseResult day_result = ParseDay(hourly, start_index);

        if (std::holds_alternative<WeatherParserError>(day_result)) {
            return std::get<WeatherParserError>(day_result);
        }

        days.push_back(std::get<WeatherDay>(day_result));
        days[i].date = std::get<std::string>(time[i * 24]);
    }

    return days;
}

DayParseResult WeatherParser::ParseDay(JsonObject& hourly, size_t start_index) {
    if (!std::holds_alternative<JsonArray>(hourly.at("temperature_2m"))) {
        return WeatherParserError("Failed to parse 'temperature_2m' as JsonArray.");
    }
    if (!std::holds_alternative<JsonArray>(hourly.at("relative_humidity_2m"))) {
        return WeatherParserError("Failed to parse 'relative_humidity_2m' as JsonArray.");
    }
    if (!std::holds_alternative<JsonArray>(hourly.at("rain"))) {
        return WeatherParserError("Failed to parse 'rain' as JsonArray.");
    }
    if (!std::holds_alternative<JsonArray>(hourly.at("cloud_cover"))) {
        return WeatherParserError("Failed to parse 'cloud_cover' as JsonArray.");
    }
    if (!std::holds_alternative<JsonArray>(hourly.at("wind_speed_10m"))) {
        return WeatherParserError("Failed to parse 'wind_speed_10m' as JsonArray.");
    }

    JsonArray& temperature_array = std::get<JsonArray>(hourly.at("temperature_2m"));
    JsonArray& humidity_array = std::get<JsonArray>(hourly.at("relative_humidity_2m"));
    JsonArray& rain_array = std::get<JsonArray>(hourly.at("rain"));
    JsonArray& cloud_cover_array = std::get<JsonArray>(hourly.at("cloud_cover"));
    JsonArray& wind_speed_array = std::get<JsonArray>(hourly.at("wind_speed_10m"));

    PeriodParseResult morning_result =
        ParsePeriod(temperature_array, humidity_array, rain_array, cloud_cover_array,
                    wind_speed_array, start_index);
    if (std::holds_alternative<WeatherParserError>(morning_result)) {
        return std::get<WeatherParserError>(morning_result);
    }

    PeriodParseResult afternoon_result =
        ParsePeriod(temperature_array, humidity_array, rain_array, cloud_cover_array,
                    wind_speed_array, start_index + 6);
    if (std::holds_alternative<WeatherParserError>(afternoon_result)) {
        return std::get<WeatherParserError>(afternoon_result);
    }

    PeriodParseResult evening_result =
        ParsePeriod(temperature_array, humidity_array, rain_array, cloud_cover_array,
                    wind_speed_array, start_index + 12);
    if (std::holds_alternative<WeatherParserError>(evening_result)) {
        return std::get<WeatherParserError>(evening_result);
    }

    PeriodParseResult night_result =
        ParsePeriod(temperature_array, humidity_array, rain_array, cloud_cover_array,
                    wind_speed_array, start_index + 18);
    if (std::holds_alternative<WeatherParserError>(night_result)) {
        return std::get<WeatherParserError>(night_result);
    }

    WeatherDay day;
    day.morning = std::get<WeatherPeriod>(morning_result);
    day.afternoon = std::get<WeatherPeriod>(afternoon_result);
    day.evening = std::get<WeatherPeriod>(evening_result);
    day.night = std::get<WeatherPeriod>(night_result);

    return day;
}

PeriodParseResult WeatherParser::ParsePeriod(const JsonArray& temperature_array,
                                             const JsonArray& humidity_array,
                                             const JsonArray& rain_array,
                                             const JsonArray& cloud_cover_array,
                                             const JsonArray& wind_speed_array,
                                             size_t index) {
    WeatherPeriod period;

    period.temperature = std::get<double>(temperature_array[index]);
    period.humidity = std::get<int64_t>(humidity_array[index]);
    period.rain = std::get<double>(rain_array[index]);
    period.cloud_cover = std::get<int64_t>(cloud_cover_array[index]);
    period.wind_speed = std::get<double>(wind_speed_array[index]);

    return period;
}
