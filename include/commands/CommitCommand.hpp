#pragma once
#include "Command.hpp"
#include <string>
using std::string;

class CommitCommand : public Command {
    string message;

public : 
     CommitCommand(const string& msg);
     void execute() override;
};