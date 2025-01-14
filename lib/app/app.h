#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <optional>

#include "configuration.h"
#include "configuration_factory.h"
#include "file_reader.h"
#include "parser.h"

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
    explicit Application(std::string& config_path);

    InitResult Init();
    RunResult Run();

private:
    FileReader file_reader_;
    std::unique_ptr<JsonParser> parser_;
    std::unique_ptr<ConfigurationFactory> factory_;

    void FetchCityCoordinates(const Configuration& config);
};
#endif  // APPLICATION_H
