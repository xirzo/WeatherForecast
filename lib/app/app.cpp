#include "app.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <optional>
#include <stdexcept>

#include "app.h"
#include "configuration_factory.h"

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

    FetchCityCoordinates(configuration);
    return std::nullopt;
}

RunResult Application::Run() {
    Element document = hbox({
        text("left") | border,
        text("middle") | border | flex,
        text("right") | border,
    });

    auto screen = Screen::Create(Dimension::Full(),        // Width
                                 Dimension::Fit(document)  // Height
    );
    Render(screen, document);
    screen.Print();

    return std::nullopt;
}

void Application::FetchCityCoordinates(const Configuration& config) {
    for (const auto& city : config.cities) {
    }
}
