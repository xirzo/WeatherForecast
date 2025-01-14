#ifndef PARSER
#define PARSER

#include <string>
#include <unordered_map>
#include <variant>

struct ParseError {
    std::string message;
};

using Json = std::unordered_map<std::string, std::string>;

using ParseResult = std::variant<Json, ParseError>;

class JsonParser {
public:
    JsonParser(std::string text);
    ParseResult Parse();

private:
    std::string text_;
    ParseResult Parse(const std::string& json_text);
    std::string Trim(const std::string& str);
};
#endif  // !PARSER
