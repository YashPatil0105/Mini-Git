#include "commands/InitCommand.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = std::filesystem;

void InitCommand :: execute() {
    if(fs::exists(".mini-git")){
        cout << "Repository already initialized.\n";
        return;
    }

    fs::create_directory(".mini-git");
    ofstream head(".mini-git/HEAD");
    head << "ref: refs/heads/master\n";
    head.close();

    fs::create_directories(".mini-git/refs/heads");
    fs::create_directory(".mini-git/objects");

    cout << "Initialized empty Mini-Git repository in .mini-git/\n";
}