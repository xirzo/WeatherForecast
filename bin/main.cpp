#include <cstdlib>
#include <iostream>

#include "app.h"

int main(void) {
    std::string config_path = "../config.json";
    Application app(config_path);

    app.Init();

    RunResult result = app.Run();

    while (result != std::nullopt) {
        std::cerr << result->message << std::endl;
        result = app.Run();
    }

    return EXIT_SUCCESS;
}
