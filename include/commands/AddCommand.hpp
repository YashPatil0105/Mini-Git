#pragma once
#include "Command.hpp"
#include <string>
using namespace std;

class AddCommand : public Command {
    string filename;

public:
    AddCommand(const string& file);
    void execute() override;
};