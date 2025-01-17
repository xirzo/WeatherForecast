#include "app.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <optional>

#include "configuration_factory.h"
#include "forecast_factory.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

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

    Forecast forecast = std::get<Forecast>(forecast_result);

    return std::nullopt;
}

Element ButtonToElement(Component button) {
    return button->Render() | size(WIDTH, LESS_THAN, 15);
}

RunResult Application::Run() {
    // auto screen = ScreenInteractive::TerminalOutput();
    //
    // int count = 0;
    //
    // auto decrease_button = Button("Decrease", [&] { count--; });
    // auto increase_button = Button("Increase", [&] { count++; });
    //
    // Elements button_elements = {decrease_button->Render(), separator(),
    //                             increase_button->Render()};
    //
    // auto buttons = hbox(button_elements) | center;
    //
    // auto renderer = Renderer([&] {
    //     return vbox({
    //                text("Count: " + std::to_string(count)) | hcenter,
    //                separator(),
    //                buttons,
    //            }) |
    //            border;
    // });
    //
    // renderer |= CatchEvent([&](Event event) -> bool {
    //     if (event == ExitKey) {
    //         screen.ExitLoopClosure()();
    //         return true;
    //     }
    //     return false;
    // });
    //
    // screen.Loop(renderer);
    return std::nullopt;
}
