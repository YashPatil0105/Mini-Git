// #include "commands/CommitCommand.hpp"
// #include "core/Commit.hpp"
// #include "repository/StagingArea.hpp"
// #include <filesystem>
// #include <fstream>
// #include <iostream>

// namespace fs = std::filesystem;

// CommitCommand::CommitCommand(const string& msg) : message(msg) {}

// void CommitCommand::execute(){
//     StagingArea stage;
//     auto staged = stage.getStagedFiles();

//     if(staged.empty()){
//         cout << "No changes staged for commit. \n";
//         return;
//     }

//     string parentHash = "";
//     ifstream head(".minigit/HEAD");
//     string ref;
//     getline(head, ref);
//     head.close();

//     string headRef = ".minigit/" + ref.substr(5); // skip "ref: "
//     ifstream headFile(headRef);
//     if (headFile) getline(headFile, parentHash);

//     Commit commit(parentHash, message, staged);
//     commit.save();


//     ofstream out(headRef);
//     out << commit.getHash() << "\n";

//     stage.clear();

//     cout << "Commited as " << commit.getHash() << "\n";
// }

#include "commands/CommitCommand.hpp"
#include "core/Commit.hpp"
#include "repository/StagingArea.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "core/Tree.hpp"

namespace fs = std::filesystem;

CommitCommand::CommitCommand(const string& msg, std::shared_ptr<StagingArea> stagingArea)
    : message(msg), staging(stagingArea) {}

void CommitCommand::execute() {
    auto staged = staging->getStagedFiles();

    if (staged.empty()) {
        std::cout << "No changes staged for commit.\n";
        return;
    }

    string parentHash = "";
    string refPath = ".mini-git/HEAD";

    ifstream head(refPath);
    if (!head) {
        cerr << "Error: HEAD reference file not found.\n";
        return;
    }

    string ref;
    getline(head, ref);
    head.close();

    if (ref.substr(0, 5) != "ref: ") {
        cerr << "Invalid HEAD ref format.\n";
        return;
    }

    string headRefPath = ".mini-git/" + ref.substr(5);
    ifstream headFile(headRefPath);
    if (headFile) {
        getline(headFile, parentHash);
        headFile.close();
    }

    // Build the root tree from the working directory
    Tree rootTree = Tree::buildFromDirectory(".");
    rootTree.save();
    string rootTreeHash = rootTree.getHash();

    Commit commit(parentHash, message, rootTreeHash);
    commit.save();

    ofstream out(headRefPath);
    if (!out) {
        cerr << "Error: Unable to write to HEAD ref path.\n";
        return;
    }
    out << commit.getHash() << "\n";
    out.close();

    staging->clear();

    cout << "Committed as " << commit.getHash() << "\n";
}
