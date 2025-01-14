#ifndef CONFIGURATION
#define CONFIGURATION

#include <string>
#include <vector>

#include "city.h"

struct Configuration {
    std::vector<City> cities;
    std::string api_key;
    int days;
    int frequency;
};

#endif  // !CONFIGURATION
