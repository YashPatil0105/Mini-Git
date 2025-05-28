#include "cli/CliParser.hpp"
#include "commands/StatusCommand.hpp"
#include "commands/CommitCommand.hpp"
#include "commands/AddCommand.hpp"
#include "commands/InitCommand.hpp"
// #include "commands/LogCommand.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::make_unique;
using std::shared_ptr;
using std::string;
using std::vector;
using std::unique_ptr;

unique_ptr<Command> CliParser::parse(int argc, char* argv[], shared_ptr<StagingArea> staging) {
    if (argc < 2) {
        return nullptr;
    }

    string command = argv[1];

    if (command == "init") {
        return make_unique<InitCommand>();
    }
    else if (command == "status") {
        return make_unique<StatusCommand>(staging);
    }
    else if (command == "commit") {
        string message = getMessageFromArgs(argc, argv);
        return make_unique<CommitCommand>(message, staging);
    }
    else if (command == "add") {
        if (argc < 3) {
            return nullptr;
        }
        string filename = argv[2];
        return make_unique<AddCommand>(filename, staging);
    }

    // else if (command == "log") {
    //     // Assuming LogCommand takes staging ptr
    //     return make_unique<LogCommand>(staging);
    // }

    return nullptr;
}

string CliParser::getMessageFromArgs(int argc, char* argv[]) {
    if (argc < 3) return "";

    string message;
    for (int i = 2; i < argc; ++i) {
        message += argv[i];
        if (i < argc - 1) message += " ";
    }
    return message;
}
