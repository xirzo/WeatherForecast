#include "converter.h"

#include <charconv>
#include <sstream>

Converter::Converter(Json json) : json_(std::move(json)) {}

ConvertResult Converter::ConvertKey(const std::string& key) {
    if (json_.find(key) == json_.end()) {
        return ConvertError{key + " is not present in the json"};
    }

    const std::string& raw_value = json_.at(key);

    if (raw_value.empty()) {
        return ConvertError{"Value string by key " + key + " is empty"};
    }

    if (auto bool_result = ConvertToBool(raw_value); std::holds_alternative<JsonValue>(bool_result)) {
        return bool_result;
    }

    if (auto int_result = ConvertToInt(raw_value); std::holds_alternative<JsonValue>(int_result)) {
        return int_result;
    }

    if (auto double_result = ConvertToDouble(raw_value); std::holds_alternative<JsonValue>(double_result)) {
        return double_result;
    }

    if (raw_value.front() == '[' && raw_value.back() == ']') {
        std::string inner = raw_value.substr(1, raw_value.size() - 2);
        std::vector<JsonValue> arr_elems;
        std::stringstream ss(inner);
        std::string elem_str;

        while (std::getline(ss, elem_str, ',')) {
            ConvertResult result = ConvertValue(elem_str);

            if (std::holds_alternative<ConvertError>(result)) {
                return ConvertError{"Error during creation of the array:" + std::get<ConvertError>(result).message};
            }

            JsonValue elem_val = std::get<JsonValue>(result);
            arr_elems.push_back(elem_val);
        }

        JsonValue json_value;
        json_value.value = arr_elems;
        return json_value;
    }

    return ConvertToString(raw_value);
}

ConvertResult Converter::ConvertValue(const std::string& value) {
    std::string trimmed = value;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

    if (trimmed.empty()) {
        return ConvertError{"Value string is empty"};
    }

    if (auto bool_result = ConvertToBool(trimmed); std::holds_alternative<JsonValue>(bool_result)) {
        return bool_result;
    }

    if (auto int_result = ConvertToInt(trimmed); std::holds_alternative<JsonValue>(int_result)) {
        return int_result;
    }

    if (auto double_result = ConvertToDouble(trimmed); std::holds_alternative<JsonValue>(double_result)) {
        return double_result;
    }

    if (trimmed.front() == '[' && trimmed.back() == ']') {
        std::string inner = trimmed.substr(1, trimmed.size() - 2);
        std::vector<JsonValue> arr_elems;
        std::stringstream ss(inner);
        std::string elem_str;

        while (std::getline(ss, elem_str, ',')) {
            ConvertResult result = ConvertValue(elem_str);

            if (std::holds_alternative<ConvertError>(result)) {
                return ConvertError{"Error during creation of the array:" + std::get<ConvertError>(result).message};
            }

            JsonValue elem_val = std::get<JsonValue>(result);
            arr_elems.push_back(elem_val);
        }

        JsonValue json_value;
        json_value.value = arr_elems;
        return json_value;
    }

    return ConvertToString(trimmed);
}

ConvertResult Converter::ConvertToBool(const std::string& raw_value) {
    if (raw_value == "true") {
        JsonValue json_value;
        json_value.value = true;
        return json_value;
    } else if (raw_value == "false") {
        JsonValue json_value;
        json_value.value = false;
        return json_value;
    }
    return ConvertError{"Invalid boolean value: " + raw_value};
}

ConvertResult Converter::ConvertToInt(const std::string& raw_value) {
    int int_value = 0;
    const char* start_ptr_int = raw_value.data();
    const char* end_ptr_int = raw_value.data() + raw_value.size();

    auto [ptr_int, ec_int] = std::from_chars(start_ptr_int, end_ptr_int, int_value);

    if (ec_int == std::errc() && ptr_int == end_ptr_int) {
        JsonValue json_value;
        json_value.value = int_value;
        return json_value;
    }

    return ConvertError{"Invalid integer value: " + raw_value};
}

ConvertResult Converter::ConvertToDouble(const std::string& raw_value) {
    double double_value = 0.0;
    const char* start_ptr_double = raw_value.data();
    const char* end_ptr_double = raw_value.data() + raw_value.size();

    auto [ptr_double, ec_double] = std::from_chars(start_ptr_double, end_ptr_double, double_value);

    if (ec_double == std::errc() && ptr_double == end_ptr_double) {
        JsonValue json_value;
        json_value.value = double_value;
        return json_value;
    }

    return ConvertError{"Invalid double value: " + raw_value};
}

ConvertResult Converter::ConvertToString(const std::string& raw_value) {
    std::string processed = raw_value;
    if (!processed.empty() && processed.front() == '\"' && processed.back() == '\"') {
        processed = processed.substr(1, processed.size() - 2);
    }
    JsonValue json_value;
    json_value.value = processed;
    return json_value;
}
