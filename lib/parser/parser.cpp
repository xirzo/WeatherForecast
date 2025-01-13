#include "parser.h"

#include "file_reader.h"
#include "sstream"

JsonParser::JsonParser() : file_reader_("../config.json") {}

ParseResult JsonParser::Parse() {
    ReadFileResult file_read_result = file_reader_.ReadFile();

    if (std::holds_alternative<FileError>(file_read_result)) {
        return ParseError{std::get<FileError>(file_read_result).message};
    }

    std::string json_text = std::get<std::string>(file_read_result);

    ParseResult parse_result = Parse(json_text);

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
    std::string pair_segment;
    bool in_array = false;
    std::string current_key;
    std::string array_values;

    while (std::getline(ss, pair_segment, ',')) {
        pair_segment = Trim(pair_segment);
        if (pair_segment.empty()) {
            continue;
        }

        if (in_array) {
            array_values += "," + pair_segment;
            if (pair_segment.find(']') != std::string::npos) {
                in_array = false;
                json[current_key] = array_values;
            }
            continue;
        }

        std::size_t colon_pos = pair_segment.find(':');
        if (colon_pos == std::string::npos) {
            continue;
        }

        std::string key_str = pair_segment.substr(0, colon_pos);
        std::string value_str = pair_segment.substr(colon_pos + 1);

        key_str = Trim(key_str);
        if (key_str.empty() == false && key_str.front() == '\"') {
            key_str.erase(0, 1);
        }
        if (key_str.empty() == false && key_str.back() == '\"') {
            key_str.pop_back();
        }

        value_str = Trim(value_str);

        if (value_str.empty() == false && value_str.front() == '[') {
            in_array = true;
            array_values = value_str;
            if (value_str.find(']') != std::string::npos) {
                in_array = false;
                json[key_str] = array_values;
            }
        } else {
            if (value_str.empty() == false && value_str.front() == '\"') {
                value_str.erase(0, 1);
            }
            if (value_str.empty() == false && value_str.back() == '\"') {
                value_str.pop_back();
            }
            json[key_str] = value_str;
        }
    }

    if (json.empty()) {
        return ParseError{"Json text file does not have any key-value pairs"};
    }

    return json;
}
