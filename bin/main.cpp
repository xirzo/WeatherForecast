#include <cstdlib>
#include <iostream>
#include <optional>

#include "app.h"

int main() {
    Application app("../../config.json");

    InitResult init_result = app.Init();

    if (init_result != std::nullopt) {
        std::cerr << init_result->message << std::endl;
        return EXIT_FAILURE;
    }

    RunResult result;

    do {
        result = app.Run();
    } while (result != std::nullopt);

    std::cerr << result->message << std::endl;
    return EXIT_FAILURE;
}
