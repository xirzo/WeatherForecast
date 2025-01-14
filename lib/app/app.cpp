#include "app.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <optional>
#include <stdexcept>

#include "configuration_factory.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

Application::Application(std::string& config_path) : file_reader_(config_path) {
    ReadFileResult read_result = file_reader_.ReadFile();

    if (std::holds_alternative<FileError>(read_result)) {
        std::string error_message = std::get<FileError>(read_result).message;
        throw std::invalid_argument(error_message);
    }

    std::string file_content = std::get<std::string>(read_result);

    parser_ = std::make_unique<JsonParser>(file_content);
    factory_ = std::make_unique<ConfigurationFactory>(*parser_);
}

InitResult Application::Init() {
    CreateResult result = factory_->Create();

    if (std::holds_alternative<CreateError>(result)) {
        return InitError{std::get<CreateError>(result).message};
    }

    Configuration configuration = std::get<Configuration>(result);

    std::cout << "Days: " << configuration.days << std::endl;
    std::cout << "Frequency: " << configuration.frequency << std::endl;
    std::cout << "API Key: " << configuration.api_key << std::endl;

    return std::nullopt;
}

// Helper function to convert Button components to Elements
Element ButtonToElement(Component button) {
    return button->Render() | size(WIDTH, LESS_THAN, 15);  // Adjust size as needed
}

RunResult Application::Run() {
    auto screen = ScreenInteractive::TerminalOutput();

    int count = 0;

    auto decrease_button = Button("Decrease", [&] { count--; });
    auto increase_button = Button("Increase", [&] { count++; });

    Elements button_elements = {decrease_button->Render(), separator(),
                                increase_button->Render()};

    auto buttons = hbox(button_elements) | center;

    auto renderer = Renderer([&] {
        return vbox({
                   text("Count: " + std::to_string(count)) | hcenter,
                   separator(),
                   buttons,
               }) |
               border;
    });

    renderer |= CatchEvent([&](Event event) -> bool {
        if (event == ExitKey) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(renderer);
    return std::nullopt;
}
