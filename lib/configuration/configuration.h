#ifndef CONFIGURATION
#define CONFIGURATION

#include <string>
#include <vector>

struct Configuration {
    std::vector<std::string> cities;
    std::string api_key;
    int days;
    int frequency;
};

#endif  // !CONFIGURATION
