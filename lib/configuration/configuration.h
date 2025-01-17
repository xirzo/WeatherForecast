#ifndef CONFIGURATION
#define CONFIGURATION

#include <cstdint>
#include <string>
#include <vector>

#include "city.h"

struct Configuration {
    std::vector<City> cities;
    std::string api_key;
    int64_t days;
    int64_t frequency;
};

#endif  // !CONFIGURATION
