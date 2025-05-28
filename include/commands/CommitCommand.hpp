#pragma once
#include "Command.hpp"
#include <string>
#include <memory>
#include "repository/StagingArea.hpp"
using std::string;

class CommitCommand : public Command {
    std::shared_ptr<StagingArea> staging;
    string message;

public : 
     CommitCommand(const string& msg, std::shared_ptr<StagingArea> stagingArea);
     void execute() override;
     std::string getCurrentBranch() const;
};