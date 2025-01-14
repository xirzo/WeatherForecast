#include "parser.h"

#include "sstream"

JsonParser::JsonParser(std::string text) : text_(std::move(text)) {}

ParseResult JsonParser::Parse() {
    ParseResult parse_result = Parse(text_);

    if (std::holds_alternative<ParseError>(parse_result)) {
        return ParseError{std::get<ParseError>(parse_result).message};
    }

    return std::get<Json>(parse_result);
}

std::string JsonParser::Trim(const std::string& str) {
    const char* whitespace = " \t\n\r\f\v";

    std::size_t start = str.find_first_not_of(whitespace);
    std::size_t end = str.find_last_not_of(whitespace);

    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }

    return str.substr(start, end - start + 1);
}

ParseResult JsonParser::Parse(const std::string& json_text) {
    Json json;

    if (json_text.empty()) {
        return ParseError{"Json text file is empty"};
    }

    std::size_t start_brace = json_text.find_first_of('{');
    std::size_t end_brace = json_text.find_last_of('}');

    if (start_brace == std::string::npos || end_brace == std::string::npos ||
        start_brace > end_brace) {
        return ParseError{"Json text file does not have valid braces"};
    }

    std::string content = json_text.substr(start_brace + 1, end_brace - start_brace - 1);
    std::stringstream ss(content);
    std::string segment;
    bool parsing_array = false;
    std::string current_key;
    std::string array_data;

    while (std::getline(ss, segment, ',')) {
        segment = Trim(segment);
        if (segment.empty()) {
            continue;
        }
        if (parsing_array) {
            array_data += "," + segment;
            if (segment.find(']') != std::string::npos) {
                parsing_array = false;
                json[current_key] = array_data;
            }
            continue;
        }

        std::size_t colon_pos = segment.find(':');

        if (colon_pos == std::string::npos) {
            continue;
        }

        std::string key = segment.substr(0, colon_pos);
        std::string value = segment.substr(colon_pos + 1);

        key = Trim(key);

        if (key.empty() == false && key.front() == '\"') {
            key.erase(0, 1);
        }

        if (key.empty() == false && key.back() == '\"') {
            key.pop_back();
        }

        value = Trim(value);

        if (value.empty() == false && value.front() == '[') {
            parsing_array = true;

            array_data = value;

            current_key = key;

            if (value.find(']') != std::string::npos) {
                parsing_array = false;
                json[current_key] = array_data;
            }
        } else {
            if (value.empty() == false && value.front() == '\"') {
                value.erase(0, 1);
            }

            if (value.empty() == false && value.back() == '\"') {
                value.pop_back();
            }

            json[key] = value;
        }
    }

    if (json.empty()) {
        return ParseError{"Json text file does not have any key-value pairs"};
    }

    return json;
}
