#include "core/Branch.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

Branch::Branch(const std::string& name, const std::string& commitHash)
    : name(name), commitHash(commitHash) {}

const std::string& Branch::getName() const {
    return name;
}

const std::string& Branch::getCommitHash() const {
    return commitHash;
}

void Branch::setCommitHash(const std::string& hash) {
    commitHash = hash;
}

void Branch::save() const {
    fs::create_directories(".mini-git/refs/heads");
    std::ofstream out(".mini-git/refs/heads/" + name);
    if (!out) {
        throw std::runtime_error("Failed to create branch file: " + name);
    }
    out << commitHash;
}

Branch Branch::load(const std::string& name) {
    std::ifstream in(".mini-git/refs/heads/" + name);
    if (!in) {
        throw std::runtime_error("Branch does not exist: " + name);
    }
    std::string commitHash;
    std::getline(in, commitHash);
    return Branch(name, commitHash);
} 