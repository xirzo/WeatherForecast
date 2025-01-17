#include "configuration_factory.h"

#include <string>
#include <variant>

#include "city.h"
#include "client.h"
#include "configuration.h"
#include "file_reader.h"
#include "parser.h"

ConfigurationFactory::ConfigurationFactory(const std::string& configuration_path)
    : parser_(JsonParser()), file_reader_(FileReader(configuration_path)) {}

CreateResult ConfigurationFactory::Create() {
    Configuration configuration;
    ReadFileResult read_result = file_reader_.ReadFile();

    if (std::holds_alternative<FileError>(read_result)) {
        return CreateError{std::get<FileError>(read_result).message};
    }

    const std::string file = std::get<std::string>(read_result);

    ParseResult parse_result = parser_.Parse(file);

    if (std::holds_alternative<ParserError>(parse_result)) {
        return CreateError{std::get<ParserError>(parse_result).message};
    }

    Json json = std::get<Json>(parse_result);

    if (std::holds_alternative<int64_t>(json.at("days")) == false) {
        return CreateError("Days property was not found");
    }

    configuration.days = std::get<int64_t>(json.at("frequency"));

    if (std::holds_alternative<int64_t>(json.at("frequency")) == false) {
        return CreateError("Frequency property was not found");
    }

    configuration.frequency = std::get<int64_t>(json.at("frequency"));

    if (std::holds_alternative<std::string>(json.at("API key")) == false) {
        return CreateError("API key was not found");
    }

    configuration.api_key = std::get<std::string>(json.at("API key"));

    if (std::holds_alternative<JsonArray>(json.at("cities")) == false) {
        return CreateError("Cities array was not found");
    }

    JsonArray cities_json = std::get<JsonArray>(json.at("cities"));

    if (cities_json.size() == 0) {
        return CreateError("Cities array is empty");
    }

    if (std::holds_alternative<std::string>(cities_json[0]) == false) {
        return CreateError("Cities array does not hold strings");
    }

    std::vector<std::string> cities;

    for (const JsonValue& value : cities_json) {
        cities.push_back(std::get<std::string>(value));
    }

    for (size_t i = 0; i < cities.size(); ++i) {
        City city;

        city.name = cities[i];

        HttpClient client("https://api.api-ninjas.com/v1");

        cpr::Parameters params;
        params.Add({{"name"}, cities[i]});

        cpr::Header header = {{"X-Api-Key", configuration.api_key}};

        auto response = client.Get("/city", params, header);

        if (response.error) {
            return CreateError{response.error.message};
        }

        ParseResult parse_result = parser_.Parse(response.text);

        if (std::holds_alternative<ParserError>(parse_result)) {
            return CreateError{std::get<ParserError>(parse_result).message};
        }

        Json json = std::get<Json>(parse_result);

        if (std::holds_alternative<double>(json.at("latitude")) == false) {
            return CreateError("Latitude was not found");
        }

        city.latitude = std::get<double>(json.at("latitude"));

        if (std::holds_alternative<double>(json.at("longitude")) == false) {
            return CreateError("Longitude was not found");
        }

        city.longitude = std::get<double>(json.at("longitude"));

        configuration.cities.push_back(city);
    }

    return configuration;
}
