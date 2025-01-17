#ifndef APPLICATION_H
#define APPLICATION_H

#include <parser.h>

#include <ftxui/component/event.hpp>
#include <memory>
#include <optional>

#include "configuration_factory.h"
#include "forecast_factory.h"

using namespace ftxui;

struct InitError {
    std::string message;
};

struct RunError {
    std::string message;
};

using InitResult = std::optional<InitError>;

using RunResult = std::optional<RunError>;

class Application {
public:
    Application(const std::string& configuration_path);

    InitResult Init();
    RunResult Run();

private:
    const Event ExitKey = Event::Escape;
    const Event NextKey = Event::N;
    const Event PreviousKey = Event::P;

    std::unique_ptr<JsonParser> parser_;
    std::unique_ptr<ConfigurationFactory> config_factory_;
    std::unique_ptr<ForecastFactory> forecast_factory_;
};
#endif  // APPLICATION_H
