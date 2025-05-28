#include "commands/CommitCommand.hpp"
#include "core/Commit.hpp"
#include "repository/StagingArea.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "core/Tree.hpp"
#include "core/Branch.hpp"

namespace fs = std::filesystem;

CommitCommand::CommitCommand(const string& msg, shared_ptr<StagingArea> staging)
    : message(msg), staging(staging) {}

string CommitCommand::getCurrentBranch() const {
    std::ifstream head(".mini-git/HEAD");
    if (!head) return "";
    
    string ref;
    std::getline(head, ref);
    if (ref.substr(0, 5) != "ref: ") return "";
    
    return ref.substr(5).substr(11); // Remove "ref: refs/heads/"
}

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

    // Build tree from staged files
    Tree rootTree;
    for (const auto& [file, hash] : staged) {
        rootTree.addEntry(EntryType::BLOB, file, hash);
    }
    rootTree.save();
    string rootTreeHash = rootTree.getHash();

    // Create and save commit
    Commit commit(parentHash, message, rootTreeHash);
    commit.save();

    // Update current branch
    string currentBranch = getCurrentBranch();
    if (!currentBranch.empty()) {
        try {
            Branch branch = Branch::load(currentBranch);
            branch.setCommitHash(commit.getHash());
            branch.save();
        } catch (const std::exception& e) {
            cerr << "Error updating branch: " << e.what() << endl;
            return;
        }
    }

    // Update HEAD
    ofstream headOut(refPath);
    if (!headOut) {
        cerr << "Error: Failed to update HEAD reference.\n";
        return;
    }
    headOut << "ref: refs/heads/" << currentBranch;
    headOut.close();

    cout << "Committed: " << commit.getHash() << endl;
    staging->clear();
}
