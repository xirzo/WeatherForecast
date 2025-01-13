#include <iostream>
#include <ostream>
#include <variant>

#include "parser.h"

int main() {
    JsonParser parser;

    ParseResult result = parser.Parse();

    if (std::holds_alternative<ParseError>(result)) {
        std::cerr << std::get<ParseError>(result).message << std::endl;
    }

    Json config = std::get<Json>(result);

    for (auto& it : config) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    return 0;
}
