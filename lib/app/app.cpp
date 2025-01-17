#include "app.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
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

    std::vector<Forecast> forecasts = std::get<std::vector<Forecast>>(forecast_result);

    for (size_t i = 0; i < forecasts.size(); i++) {
        std::cout << forecasts[i].city_name << std::endl;

        for (size_t j = 0; j < forecasts.size(); j++) {
            std::cout << forecasts[i].days[j].date << std::endl;

            std::cout << "Morning:" << std::endl;
            std::cout << "  Humidity: " << forecasts[i].days[j].morning.humidity
                      << std::endl;
            std::cout << "  Cloud Cover: " << forecasts[i].days[j].morning.cloud_cover
                      << std::endl;
            std::cout << "  Temperature: " << forecasts[i].days[j].morning.temperature
                      << std::endl;
            std::cout << "  Wind Speed: " << forecasts[i].days[j].morning.wind_speed
                      << std::endl;
            std::cout << "  Rain: " << forecasts[i].days[j].morning.rain << std::endl;

            std::cout << "Afternoon:" << std::endl;
            std::cout << "  Humidity: " << forecasts[i].days[j].afternoon.humidity
                      << std::endl;
            std::cout << "  Cloud Cover: " << forecasts[i].days[j].afternoon.cloud_cover
                      << std::endl;
            std::cout << "  Temperature: " << forecasts[i].days[j].afternoon.temperature
                      << std::endl;
            std::cout << "  Wind Speed: " << forecasts[i].days[j].afternoon.wind_speed
                      << std::endl;
            std::cout << "  Rain: " << forecasts[i].days[j].afternoon.rain << std::endl;

            std::cout << "Evening:" << std::endl;
            std::cout << "  Humidity: " << forecasts[i].days[j].evening.humidity
                      << std::endl;
            std::cout << "  Cloud Cover: " << forecasts[i].days[j].evening.cloud_cover
                      << std::endl;
            std::cout << "  Temperature: " << forecasts[i].days[j].evening.temperature
                      << std::endl;
            std::cout << "  Wind Speed: " << forecasts[i].days[j].evening.wind_speed
                      << std::endl;
            std::cout << "  Rain: " << forecasts[i].days[j].evening.rain << std::endl;

            std::cout << "Night:" << std::endl;
            std::cout << "  Humidity: " << forecasts[i].days[j].night.humidity
                      << std::endl;
            std::cout << "  Cloud Cover: " << forecasts[i].days[j].night.cloud_cover
                      << std::endl;
            std::cout << "  Temperature: " << forecasts[i].days[j].night.temperature
                      << std::endl;
            std::cout << "  Wind Speed: " << forecasts[i].days[j].night.wind_speed
                      << std::endl;
            std::cout << "  Rain: " << forecasts[i].days[j].night.rain << std::endl;
        }
    }

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
    return RunError("Exit key pressed");
}
