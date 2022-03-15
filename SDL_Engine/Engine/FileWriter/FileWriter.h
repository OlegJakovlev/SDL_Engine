#pragma once

#ifndef FileWriter_H
#define FileWriter_H

#include <string>
#include <fstream>

class FileWriter {
public:
    enum class Mode {
        WRITE,
        WRITE_END_OF_STREAM,
        APPEND,
        TRUNCATE,
        BINARY
    };

    virtual void WriteToFile(const std::string& fileName, const std::string& textToWrite, Mode openMode);

protected:
    FileWriter() = default;
    ~FileWriter() = default;
};

#endif