#include <iostream>
#include <optional>

#include "app.h"

int main() {
    Application app("./config.json");

    InitResult init_result = app.Init();

    if (init_result != std::nullopt) {
        std::cerr << init_result->message << std::endl;
        return EXIT_FAILURE;
    }

    RunResult result = app.Run();

    if (result.has_value() == false) {
        std::cerr << result->message << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
