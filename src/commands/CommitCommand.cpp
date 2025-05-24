#include "commands/CommitCommand.hpp"
#include "core/Commit.hpp"
#include "repository/StagingArea.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

CommitCommand::CommitCommand(const string& msg) : message(msg) {}

void CommitCommand::execute(){
    StagingArea stage;
    auto staged = stage.getStagedFiles();

    if(staged.empty()){
        cout << "No changes staged for commit. \n";
        return;
    }

    string parentHash = "";
    ifstream head(".minigit/HEAD");
    string ref;
    getline(head, ref);
    head.close();

    string headRef = ".minigit/" + ref.substr(5); // skip "ref: "
    ifstream headFile(headRef);
    if (headFile) getline(headFile, parentHash);

    Commit commit(parentHash, message, staged);
    commit.save();


    ofstream out(headRef);
    out << commit.getHash() << "\n";

    stage.clear();

    cout << "Commited as " << commit.getHash() << "\n";
}