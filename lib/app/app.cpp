#include "app.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <optional>

#include "configuration_factory.h"
#include "forecast_factory.h"
#include "ui.h"

Application::Application(const std::string& configuration_path) {
    parser_ = std::make_unique<JsonParser>();
    config_factory_ = std::make_unique<ConfigurationFactory>(configuration_path);
}

InitResult Application::Init() {
    CreateResult config_result = config_factory_->Create();

    if (std::holds_alternative<CreateError>(config_result)) {
        return InitError{std::get<CreateError>(config_result).message};
    }

    Configuration configuration = std::get<Configuration>(config_result);

    forecast_factory_ = std::make_unique<ForecastFactory>(configuration);

    ForecastCreateResult forecast_result = forecast_factory_->Create();

    if (std::holds_alternative<ForecastCreateError>(forecast_result)) {
        return InitError{std::get<ForecastCreateError>(forecast_result).message};
    }

    forecasts_ = std::get<std::vector<Forecast>>(forecast_result);

    return std::nullopt;
}

Element ButtonToElement(Component button) {
    return button->Render() | size(WIDTH, LESS_THAN, 15);
}

RunResult Application::Run() {
    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    int32_t selected_day = 0;

    std::shared_ptr<ForecastComponent> component =
        Make<ForecastComponent>(forecasts_[0], selected_day, screen.ExitLoopClosure());

    Component renderer = Renderer(component, [&] { return component->Render(); });

    screen.Loop(renderer);
    return RunError("Unreachable exit");
}
