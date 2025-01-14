#ifndef CONVERTER_H
#define CONVERTER_H

#include <variant>

#include "json_value.h"
#include "parser.h"

struct ConvertError {
    std::string message;
};

using ConvertResult = std::variant<JsonValue, ConvertError>;

class Converter {
public:
    explicit Converter(Json json);

    ConvertResult ConvertKey(const std::string& key);

private:
    Json json_;

    ConvertResult ConvertValue(const std::string& value);
    ConvertResult ConvertToBool(const std::string& raw_value);
    ConvertResult ConvertToInt(const std::string& raw_value);
    ConvertResult ConvertToDouble(const std::string& raw_value);
    ConvertResult ConvertToString(const std::string& raw_value);
};

#endif  // !CONVERTER_H
#define CONVERTER_H
