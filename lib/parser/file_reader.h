#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <variant>

struct FileError {
    std::string message;
};

using ReadFileResult = std::variant<std::string, FileError>;

class FileReader {
public:
    FileReader(const std::string filepath);

    ReadFileResult ReadFile();

private:
    std::string filepath_;
};

#endif  // !FILE_READER
