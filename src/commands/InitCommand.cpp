#include "commands/InitCommand.hpp"
#include "core/Branch.hpp"
#include "core/Commit.hpp"
#include "core/Tree.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = std::filesystem;

void InitCommand::execute() {
    if(fs::exists(".mini-git")){
        cout << "Repository already initialized.\n";
        return;
    }

    // Create repository structure
    fs::create_directory(".mini-git");
    fs::create_directories(".mini-git/refs/heads");
    fs::create_directory(".mini-git/objects");

    // Create initial empty commit
    Tree rootTree;
    rootTree.save();
    string rootTreeHash = rootTree.getHash();
    
    Commit initialCommit("", "Initial commit", rootTreeHash);
    initialCommit.save();

    // Create main branch pointing to initial commit
    Branch mainBranch("main", initialCommit.getHash());
    mainBranch.save();

    // Set HEAD to point to main branch
    ofstream head(".mini-git/HEAD");
    head << "ref: refs/heads/main\n";
    head.close();

    cout << "Initialized empty Mini-Git repository in .mini-git/\n";
}