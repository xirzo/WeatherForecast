#include "app.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <optional>
#include <stdexcept>

#include "app.h"
#include "configuration_factory.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

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

    FetchCityCoordinates(configuration);
    return std::nullopt;
}

std::string Code(Event event) {
    std::string codes;

    for (auto& it : event.input()) {
        codes += " " + std::to_string((unsigned int)it);
    }

    return codes;
}

RunResult Application::Run() {
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<Event> keys;

    auto left_column = Renderer([&] {
        Elements children = {
            text("Codes"),
            separator(),
        };
        for (size_t i = std::max(0, (int)keys.size() - 20); i < keys.size(); ++i) {
            children.push_back(text(Code(keys[i])));
        }
        return vbox(children);
    });

    auto right_column = Renderer([&] {
        Elements children = {
            text("Event"),
            separator(),
        };
        for (size_t i = std::max(0, (int)keys.size() - 20); i < keys.size(); ++i) {
            children.push_back(text(keys[i].DebugString()));
        }
        return vbox(children);
    });

    int split_size = 40;

    auto component = ResizableSplitLeft(left_column, right_column, &split_size);
    component |= border;

    component |= CatchEvent([&](Event event) {
        keys.push_back(event);

        if (event == ExitKey) {
            screen.ExitLoopClosure()();
            return true;
        }

        return false;
    });

    screen.Loop(component);

    return std::nullopt;
}

void Application::FetchCityCoordinates(const Configuration& config) {
    for (const auto& city : config.cities) {
    }
}
