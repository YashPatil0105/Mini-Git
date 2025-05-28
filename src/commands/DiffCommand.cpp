#include "commands/DiffCommand.hpp"
#include "utils/Diff.hpp"
#include "core/Blob.hpp"
#include "core/Commit.hpp"
#include "core/Tree.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

DiffCommand::DiffCommand(const std::string& filePath)
    : filePath(filePath) {}

void DiffCommand::execute() {
    try {
        // Read current file content
        if (!fs::exists(filePath)) {
            std::cerr << "File does not exist: " << filePath << std::endl;
            return;
        }

        std::ifstream currentFile(filePath);
        std::string currentContent((std::istreambuf_iterator<char>(currentFile)),
                                 std::istreambuf_iterator<char>());
        currentFile.close();

        // Get the last committed version
        std::string lastCommitHash;
        std::ifstream head(".mini-git/HEAD");
        if (!head) {
            std::cerr << "HEAD file not found" << std::endl;
            return;
        }

        std::string ref;
        std::getline(head, ref);
        head.close();

        if (ref.substr(0, 5) != "ref: ") {
            std::cerr << "Invalid HEAD ref format" << std::endl;
            return;
        }

        std::string branchPath = ".mini-git/" + ref.substr(5);
        std::ifstream branch(branchPath);
        if (!branch) {
            std::cerr << "Branch file not found" << std::endl;
            return;
        }

        std::getline(branch, lastCommitHash);
        branch.close();

        // Load the commit
        Commit commit = Commit::load(lastCommitHash);
        
        // Load the commit's tree
        Tree rootTree = Tree::load(commit.getTreeHash());
        
        // Find the file's blob hash in the tree
        std::string blobHash = rootTree.findBlobHash(filePath);
        if (blobHash.empty()) {
            std::cout << "File was not in last commit\n";
            std::vector<std::string> currentLines = Diff::splitIntoLines(currentContent);
            std::vector<std::string> lastLines;
            auto changes = Diff::generateDiff(lastLines, currentLines);
            std::cout << "Changes in " << filePath << ":\n";
            std::cout << Diff::formatDiff(changes);
            return;
        }

        // Load the blob
        Blob lastBlob = Blob::load(blobHash);
        std::string lastContent = lastBlob.getContent();

        // Generate and display diff
        std::vector<std::string> currentLines = Diff::splitIntoLines(currentContent);
        std::vector<std::string> lastLines = Diff::splitIntoLines(lastContent);
        auto changes = Diff::generateDiff(lastLines, currentLines);
        std::cout << "Changes in " << filePath << ":\n";
        std::cout << Diff::formatDiff(changes);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
} 