#pragma once
#include "commands/Command.hpp"
#include <string>

class DiffCommand : public Command {
public:
    DiffCommand(const std::string& filePath);
    void execute() override;

private:
    std::string filePath;
}; 