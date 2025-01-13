#ifndef PARSER
#define PARSER

#include <unordered_map>
#include <variant>

#include "file_reader.h"

struct ParseError {
    std::string message;
};

using Json = std::unordered_map<std::string, std::string>;

using ParseResult = std::variant<Json, ParseError>;

class JsonParser {
public:
    JsonParser();
    ParseResult Parse();

private:
    FileReader file_reader_;

    ParseResult Parse(const std::string& json_text);
    std::string Trim(const std::string& str);
};
#endif  // !PARSER
