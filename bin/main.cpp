#include <cstdlib>
#include <iostream>
#include <optional>

#include "app.h"

int main(void) {
    Application app("../config.json");

    InitResult init_result = app.Init();

    if (init_result != std::nullopt) {
        std::cerr << init_result->message << std::endl;
    }

    RunResult result = app.Run();

    while (result != std::nullopt) {
        std::cerr << result->message << std::endl;
        result = app.Run();
    }

    return EXIT_SUCCESS;
}
