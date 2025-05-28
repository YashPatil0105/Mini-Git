#pragma once
#include "Command.hpp"
#include <string>
#include "repository/StagingArea.hpp"
#include <memory>
using namespace std;

class AddCommand : public Command {
    string filename;
    // StagingArea& staging;
    shared_ptr<StagingArea> staging;

public:
    AddCommand(const string& file, shared_ptr<StagingArea> stagingArea);
    void execute() override;
};