#include "FileWriter.h"

void FileWriter::WriteToFile(const std::string& fileName, const std::string& textToWrite, Mode openMode) {
    std::fstream fileToWrite;

    // Open in selected mode
    switch (openMode) {

    case Mode::WRITE:
        fileToWrite.open(fileName, std::ios_base::out);
        break;

    case Mode::WRITE_END_OF_STREAM:
        fileToWrite.open(fileName, std::ios_base::ate);
        break;

    case Mode::APPEND:
        fileToWrite.open(fileName, std::ios_base::app);
        break;

    case Mode::TRUNCATE:
        fileToWrite.open(fileName, std::ios_base::trunc);
        break;

    case Mode::BINARY:
        fileToWrite.open(fileName, std::ios_base::binary);
        break;

    default:
        return;
    }

    if (!fileToWrite.is_open()) return;

    fileToWrite << textToWrite << "\n";

    fileToWrite.close();
}
