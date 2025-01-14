#include "app.h"

int main() {
    std::string config_path = "../config.json";
    Application app(config_path);

    app.Run();
    return 0;
}
