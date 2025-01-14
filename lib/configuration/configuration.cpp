#include "configuration.h"

#include <charconv>
#include <sstream>
#include <variant>

#include "parser.h"

std::string Trim(const std::string& str) {
    const char* whitespace = " \t\n\r\f\v";

    std::size_t start = str.find_first_not_of(whitespace);
    std::size_t end = str.find_last_not_of(whitespace);

    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }

    return str.substr(start, end - start + 1);
}

CreateResult ConfigurationFactory::Create() {
    ParseResult parse_result = parser_.Parse();

    if (std::holds_alternative<ParseError>(parse_result)) {
        return CreateError{std::get<ParseError>(parse_result).message};
    }

    Json json = std::get<Json>(parse_result);

    Configuration configuration;

    if (json.find("days") == json.end()) {
        return CreateError{"Days property is not found in the configuration file"};
    }

    const std::string& days_str = json.at("days");

    auto days_parse_error = std::from_chars(
        days_str.data(), days_str.data() + days_str.size(), configuration.days);

    if (days_parse_error.ec != std::errc()) {
        return CreateError{"Failed to parse days property"};
    }

    if (json.find("frequency") == json.end()) {
        return CreateError{"Frequency is not found in the configuration file"};
    }

    const std::string& frequency_str = json.at("frequency");

    auto frequency_parse_result =
        std::from_chars(frequency_str.data(), frequency_str.data() + frequency_str.size(),
                        configuration.frequency);

    if (frequency_parse_result.ec != std::errc()) {
        return CreateError{"Failed to parse frequency property"};
    }

    if (json.find("API key") == json.end()) {
        return CreateError{"API key is not found in the configuration file"};
    }

    configuration.api_key = json["API key"];

    if (json.find("cities") == json.end()) {
        return CreateError{"Cities is not found in the configuration file"};
    }

    std::string cities_str = json["cities"];

    cities_str = cities_str.substr(1, cities_str.size() - 2);

    std::stringstream ss(cities_str);
    std::string city;

    while (std::getline(ss, city, ',')) {
        city = Trim(city);

        if (city.empty() == false && city.front() == '\"') {
            city.erase(0, 1);
        }

        if (city.empty() == false && city.back() == '\"') {
            city.pop_back();
        }

        configuration.cities.push_back(city);
    }

    return configuration;
}
