// #pragma once
// #include "commands/Command.hpp"
// #include "repository/StagingArea.hpp"

// class StatusCommand : public Command {
//     StagingArea& staging;

// public:
//     StatusCommand(StagingArea& stagingArea);
//     void execute() override;
// };
#pragma once
#include "Command.hpp"
#include "repository/StagingArea.hpp"
#include <memory>

class StatusCommand : public Command {
    std::shared_ptr<StagingArea> staging;

public:
    StatusCommand(std::shared_ptr<StagingArea> stagingArea);
    void execute() override;
};
