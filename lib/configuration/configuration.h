#ifndef CONFIGURATION
#define CONFIGURATION

#include <string>
#include <vector>

#include "parser.h"

struct Configuration {
    std::vector<std::string> cities;
    std::string api_key;
    int days;
    int frequency;
};

struct CreateError {
    std::string message;
};

using CreateResult = std::variant<Configuration, CreateError>;

class ConfigurationFactory {
public:
    CreateResult Create();

private:
    JsonParser parser_;
};

#endif  // !CONFIGURATION
