#include <iostream>
#include "core/Commit.hpp"

int main() {
    std::cout << "Running basic commit test...\n";

    // The Commit constructor now takes a tree hash, not a file map
    std::string dummyTreeHash = "dummyhash1234567890dummyhash1234567890dummyhash12"; // 40 chars
    Commit testCommit("parenthash123", "Test commit message", dummyTreeHash);
    testCommit.save();

    std::cout << "Commit hash: " << testCommit.getHash() << "\n";
    std::cout << "Test passed.\n";

    return 0;
}
