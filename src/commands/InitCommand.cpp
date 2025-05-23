#include "commands/InitCommand.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = std::filesystem;

void InitCommand :: execute() {
    if(fs::exists(".minigit")){
        cout << "Repository already initialized.\n";
        return;
    }

    fs::create_directory(".minigit");
    ofstream head(".minigit/HEAD");
    head << "ref: refs/heads/master\n";
    head.close();

    fs::create_directories(".minigit/refs/heads");
    fs::create_directory(".minigit/objects");

    cout << "Initialized empty Mini-Git repository in .minigit/\n";
}