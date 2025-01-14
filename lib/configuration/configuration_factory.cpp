#include "configuration_factory.h"

#include <string>
#include <variant>

#include "configuration.h"
#include "parser.h"

ExtractResult ConfigurationFactory::ExtractStrings(
    const std::vector<JsonValue>& jsonValues) {
    std::vector<std::string> strings;
    for (const auto& jsonValue : jsonValues) {
        if (std::holds_alternative<std::string>(jsonValue.value)) {
            strings.emplace_back(std::get<std::string>(jsonValue.value));
        } else {
            return ExtractionError{"One or more elements in 'cities' are not strings."};
        }
    }
    return strings;
}

std::string ConfigurationFactory::Trim(const std::string& str) {
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

    Converter converter(json);

    Configuration configuration;

    ConvertResult days_result = converter.ConvertKey("days");

    if (std::holds_alternative<ConvertError>(days_result)) {
        return CreateError{"Days conversion error: " +
                           std::get<ConvertError>(days_result).message};
    }

    if (!std::holds_alternative<int>(std::get<JsonValue>(days_result).value)) {
        return CreateError{"Days property is not an integer"};
    }

    configuration.days = std::get<int>(std::get<JsonValue>(days_result).value);

    ConvertResult frequency_result = converter.ConvertKey("frequency");

    if (std::holds_alternative<ConvertError>(frequency_result)) {
        return CreateError{"Frequency conversion error: " +
                           std::get<ConvertError>(frequency_result).message};
    }

    if (!std::holds_alternative<int>(std::get<JsonValue>(frequency_result).value)) {
        return CreateError{"Frequency property is not an integer"};
    }

    configuration.frequency = std::get<int>(std::get<JsonValue>(frequency_result).value);

    ConvertResult api_result = converter.ConvertKey("API key");

    if (std::holds_alternative<ConvertError>(api_result)) {
        return CreateError{"API Key conversion error: " +
                           std::get<ConvertError>(api_result).message};
    }

    if (!std::holds_alternative<std::string>(std::get<JsonValue>(api_result).value)) {
        return CreateError{"API key property is not a string"};
    }

    configuration.api_key = std::get<std::string>(std::get<JsonValue>(api_result).value);

    ConvertResult cities_result = converter.ConvertKey("cities");

    if (std::holds_alternative<ConvertError>(cities_result)) {
        return CreateError{"Cities conversion error: " +
                           std::get<ConvertError>(cities_result).message};
    }

    const JsonValue& jsonValue = std::get<JsonValue>(cities_result);

    if (!std::holds_alternative<std::vector<JsonValue>>(jsonValue.value)) {
        return CreateError{"Cities property is not an array."};
    }

    const std::vector<JsonValue>& jsonCities =
        std::get<std::vector<JsonValue>>(jsonValue.value);

    auto cities_extraction = ExtractStrings(jsonCities);

    if (std::holds_alternative<ExtractionError>(cities_extraction)) {
        return CreateError{"Cities extraction error: " +
                           std::get<ExtractionError>(cities_extraction).message};
    }

    configuration.cities = std::get<std::vector<std::string>>(cities_extraction);

    return configuration;
}
