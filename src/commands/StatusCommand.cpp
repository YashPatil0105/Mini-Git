// #include "commands/StatusCommand.hpp"
// #include "core/Blob.hpp"
// #include <filesystem>
// #include <iostream>
// #include <fstream>

// namespace fs = std::filesystem;

// StatusCommand::StatusCommand(StagingArea& stagingArea) : staging(stagingArea) {}

// void StatusCommand::execute() {
//     std::cout << "=== Mini-Git Status ===\n";

//     // Show staged files
//     const auto& stagedFiles = staging.getStagedFiles();
//     if (stagedFiles.empty()) {
//         std::cout << "No files staged for commit.\n";
//     } else {
//         std::cout << "Files staged for commit:\n";
//         for (const auto& [file, hash] : stagedFiles) {
//             std::cout << "  " << file << "\n";
//         }
//     }

//     // Check all files in current directory
//     std::cout << "\nChanges not staged for commit:\n";

//     bool hasChanges = false;
//     for (const auto& entry : fs::directory_iterator(".")) {
//         if (entry.is_regular_file()) {
//             std::string filename = entry.path().filename().string();

//             // Skip the .minigit folder and hidden files
//             if (filename == ".mini-git" || filename[0] == '.') continue;

//             // If file is staged, check if modified by comparing content hash
//             auto it = stagedFiles.find(filename);
//             if (it != stagedFiles.end()) {
//                 // Compare current file hash with staged hash
//                 std::ifstream fileStream(filename);
//                 std::string content((std::istreambuf_iterator<char>(fileStream)),
//                                      std::istreambuf_iterator<char>());
//                 fileStream.close();

//                 Blob blob(filename);
//                 std::string currentHash = blob.getHash();

//                 if (currentHash != it->second) {
//                     std::cout << "  modified: " << filename << "\n";
//                     hasChanges = true;
//                 }
//             } else {
//                 // File not staged, so untracked
//                 std::cout << "  untracked: " << filename << "\n";
//                 hasChanges = true;
//             }
//         }
//     }

//     if (!hasChanges) {
//         std::cout << "  (no changes)\n";
//     }
// }

#include "commands/StatusCommand.hpp"
#include "core/Blob.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "core/Tree.hpp"
#include "core/Commit.hpp"

namespace fs = std::filesystem;

// StatusCommand::StatusCommand(StagingArea& stagingArea) : staging(stagingArea) {}
StatusCommand::StatusCommand(std::shared_ptr<StagingArea> stagingArea) : staging(stagingArea) {}


void StatusCommand::execute() {
    std::cout << "=== Mini-Git Status ===\n";

    const auto& stagedFiles = staging->getStagedFiles();

    // Print staged files
    if (stagedFiles.empty()) {
        std::cout << "No files staged for commit.\n";
    } else {
        std::cout << "Files staged for commit:\n";
        for (const auto& [file, hash] : stagedFiles) {
            std::cout << "  " << file << "\n";
        }
    }

    std::cout << "\nChanges not staged for commit:\n";
    bool hasChanges = false;

    // Load last committed root tree hash
    std::string headPath = ".mini-git/HEAD";
    std::string latestHash;
    if (fs::exists(headPath)) {
        std::ifstream headFile(headPath);
        std::getline(headFile, latestHash);
        headFile.close();
    }
    if (!latestHash.empty()) {
        // Try to load the commit and print its root tree hash
        try {
            Commit lastCommit = Commit::load(latestHash);
            std::cout << "Last commit root tree hash: " << lastCommit.getTreeHash() << "\n";
        } catch (...) {
            std::cout << "(Could not load last commit)\n";
        }
    }

    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();

            if (filename == ".mini-git" || filename[0] == '.') continue;

            std::ifstream fileStream(filename);
            std::string content((std::istreambuf_iterator<char>(fileStream)),
                                 std::istreambuf_iterator<char>());
            fileStream.close();

            Blob blob(filename);
            std::string currentHash = blob.getHash();

            if (stagedFiles.find(filename) != stagedFiles.end()) {
                if (currentHash != stagedFiles.at(filename)) {
                    std::cout << "  modified (staged): " << filename << "\n";
                    hasChanges = true;
                }
            } else {
                std::cout << "  untracked: " << filename << "\n";
                hasChanges = true;
            }
        }
    }

    if (!hasChanges) {
        std::cout << "  (no changes)\n";
    }
}
