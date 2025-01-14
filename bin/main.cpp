#include <iostream>
#include <ostream>
#include <variant>

#include "configuration.h"
#include "request.h"

int main() {
    ConfigurationFactory factory;

    CreateResult result = factory.Create();

    if (std::holds_alternative<CreateError>(result)) {
        std::cerr << std::get<CreateError>(result).message << std::endl;
    }

    Configuration configuration = std::get<Configuration>(result);

    std::cout << configuration.days << std::endl;
    std::cout << configuration.frequency << std::endl;
    std::cout << configuration.api_key << std::endl;

    for (size_t i = 0; i < configuration.cities.size(); ++i) {
        get_lat_lon_by_city_name(configuration.cities[i]);
    }

    return 0;
}
