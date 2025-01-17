#ifndef CONFIGURATION_FACTORY_H
#define CONFIGURATION_FACTORY_H

#include <string>
#include <variant>
#include <vector>

#include "configuration.h"
#include "file_reader.h"
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
    ConfigurationFactory(const std::string& configuration_path);
    CreateResult Create();

private:
    JsonParser parser_;
    FileReader file_reader_;
};

#endif  // CONFIGURATION_FACTORY_H
