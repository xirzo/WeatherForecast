#ifndef CONFIGURATION_FACTORY_H
#define CONFIGURATION_FACTORY_H

#include <string>
#include <variant>
#include <vector>

#include "configuration.h"
#include "converter.h"
#include "parser.h"

struct CreateError {
    std::string message;
};

struct ExtractionError {
    std::string message;
};

using CreateResult = std::variant<Configuration, CreateError>;
using ExtractResult = std::variant<std::vector<std::string>, ExtractionError>;

class ConfigurationFactory {
public:
    ConfigurationFactory(JsonParser& parser);
    CreateResult Create();

private:
    JsonParser parser_;
    ExtractResult ExtractStrings(const std::vector<JsonValue>& jsonValues);
    std::string Trim(const std::string& str);
};

#endif  // CONFIGURATION_FACTORY_H
