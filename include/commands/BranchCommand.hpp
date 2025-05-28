#pragma once
#include "commands/Command.hpp"
#include <string>

class BranchCommand : public Command {
public:
    BranchCommand(const std::string& branchName, bool create);
    void execute() override;

private:
    void createBranch();
    void switchBranch();
    std::string branchName;
    bool create;
    std::string getCurrentCommit() const;
}; 