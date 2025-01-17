#include "file_reader.h"

#include <fstream>
#include <iterator>

FileReader::FileReader(const std::string &filepath) : filepath_(std::move(filepath)) {}

ReadFileResult FileReader::ReadFile() {
    std::ifstream file(filepath_);

    if (file.is_open() == false) {
        return FileError{"Failed to open the file: " + filepath_};
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    return content;
}
