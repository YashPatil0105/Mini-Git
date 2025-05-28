#include <gtest/gtest.h>
#include "core/Commit.hpp"
#include "core/Tree.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class CommitTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test directory
        fs::create_directories("test_files");
        
        // Create test file
        std::ofstream file("test_files/test.txt");
        file << "Test content";
        file.close();
    }

    void TearDown() override {
        // Clean up test files
        fs::remove_all("test_files");
        fs::remove_all(".mini-git");
    }
};

TEST_F(CommitTest, CreateCommit) {
    // Build tree
    Tree tree = Tree::buildFromDirectory("test_files");
    tree.save();
    
    // Create commit
    Commit commit("", "Initial commit", tree.getHash());
    
    // Check commit properties
    EXPECT_FALSE(commit.getHash().empty());
    EXPECT_EQ(commit.getTreeHash(), tree.getHash());
    EXPECT_EQ(commit.getParent(), "");
    EXPECT_EQ(commit.getMessage(), "Initial commit");
}

TEST_F(CommitTest, SaveAndLoadCommit) {
    // Build tree
    Tree tree = Tree::buildFromDirectory("test_files");
    tree.save();
    
    // Create and save commit
    Commit commit("", "Test commit", tree.getHash());
    commit.save();
    
    // Load commit
    Commit loadedCommit = Commit::load(commit.getHash());
    
    // Check properties
    EXPECT_EQ(loadedCommit.getHash(), commit.getHash());
    EXPECT_EQ(loadedCommit.getTreeHash(), tree.getHash());
    EXPECT_EQ(loadedCommit.getParent(), "");
    EXPECT_EQ(loadedCommit.getMessage(), "Test commit");
}

TEST_F(CommitTest, CommitWithParent) {
    // Build tree
    Tree tree = Tree::buildFromDirectory("test_files");
    tree.save();
    
    // Create parent commit
    Commit parent("", "Parent commit", tree.getHash());
    parent.save();
    
    // Create child commit
    Commit child(parent.getHash(), "Child commit", tree.getHash());
    
    // Check parent relationship
    EXPECT_EQ(child.getParent(), parent.getHash());
}

TEST_F(CommitTest, CommitHashUniqueness) {
    // Build tree
    Tree tree = Tree::buildFromDirectory("test_files");
    tree.save();
    
    // Create two commits with different messages
    Commit commit1("", "First commit", tree.getHash());
    Commit commit2("", "Second commit", tree.getHash());
    
    // Check that hashes are different
    EXPECT_NE(commit1.getHash(), commit2.getHash());
}

TEST_F(CommitTest, LoadNonExistentCommit) {
    // Try to load a commit that doesn't exist
    EXPECT_THROW(Commit::load("nonexistent_hash"), std::runtime_error);
}
