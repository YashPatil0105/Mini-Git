#pragma once
#include "Command.hpp"
#include <string>
#include "repository/StagingArea.hpp"
using namespace std;

class AddCommand : public Command {
    string filename;
    StagingArea& staging;

public:
    AddCommand(const string& file, StagingArea& stagingArea);
    void execute() override;
};