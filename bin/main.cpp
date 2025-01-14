#include <cstdlib>
#include <optional>

#include "app.h"

int main(void) {
    std::string config_path = "../config.json";
    Application app(config_path);

    app.Init();

    RunResult result;

    while (result != std::nullopt) {
        result = app.Run();
    }

    return EXIT_SUCCESS;
}
