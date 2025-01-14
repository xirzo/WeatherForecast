#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <string>
#include <variant>
#include <vector>

struct JsonValue {
    using ValueType =
        std::variant<std::string, double, int, bool, std::vector<JsonValue> >;

    ValueType value;
};

#endif  // JSON_VALUE_H
