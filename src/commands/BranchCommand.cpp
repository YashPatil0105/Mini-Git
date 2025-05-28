#include "commands/BranchCommand.hpp"
#include "core/Branch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

BranchCommand::BranchCommand(const std::string& branchName, bool create)
    : branchName(branchName), create(create) {}

std::string BranchCommand::getCurrentCommit() const {
    std::ifstream head(".mini-git/HEAD");
    if (!head) {
        throw std::runtime_error("HEAD file not found");
    }
    std::string ref;
    std::getline(head, ref);
    if (ref.substr(0, 5) != "ref: ") {
        return ref; // Direct commit hash
    }
    std::string branchPath = ".mini-git/" + ref.substr(5);
    std::ifstream branch(branchPath);
    if (!branch) {
        throw std::runtime_error("Branch file not found: " + ref.substr(5));
    }
    std::string commitHash;
    std::getline(branch, commitHash);
    return commitHash;
}

void BranchCommand::execute() {
    try {
        if (create) {
            // Create new branch
            std::string currentCommit = getCurrentCommit();
            Branch branch(branchName, currentCommit);
            branch.save();
            std::cout << "Created branch: " << branchName << std::endl;
        } else {
            // Switch to existing branch
            std::string branchPath = ".mini-git/refs/heads/" + branchName;
            if (!fs::exists(branchPath)) {
                std::cerr << "Branch does not exist: " << branchName << std::endl;
                return;
            }
            std::ofstream head(".mini-git/HEAD");
            if (!head) {
                throw std::runtime_error("Failed to update HEAD");
            }
            head << "ref: refs/heads/" << branchName;
            std::cout << "Switched to branch: " << branchName << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
} 