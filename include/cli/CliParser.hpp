
#pragma once
#include <memory>
#include "commands/Command.hpp"
#include "repository/StagingArea.hpp"

class CliParser {
public:
    static std::unique_ptr<Command> parse(int argc, char* argv[], std::shared_ptr<StagingArea> staging);
    private:
    static std::string getMessageFromArgs(int argc, char* argv[]);
};
