#include <gtest/gtest.h>
#include "core/Tree.hpp"
#include "core/Blob.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class TreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test directory structure
        fs::create_directories("test_files/dir1");
        fs::create_directories("test_files/dir2");

        // Create test files
        std::ofstream file1("test_files/file1.txt");
        std::ofstream file2("test_files/dir1/file2.txt");
        std::ofstream file3("test_files/dir2/file3.txt");
        
        file1 << "Content 1";
        file2 << "Content 2";
        file3 << "Content 3";
        
        file1.close();
        file2.close();
        file3.close();
    }

    void TearDown() override {
        // Clean up test files
        fs::remove_all("test_files");
        fs::remove_all(".mini-git");
    }
};

TEST_F(TreeTest, BuildTreeFromDirectory) {
    // Build tree from test directory
    Tree tree = Tree::buildFromDirectory("test_files");
    
    // Save tree
    tree.save();
    
    // Check that tree has entries
    const auto& entries = tree.getEntries();
    EXPECT_FALSE(entries.empty());
    
    // Check that tree hash is not empty
    EXPECT_FALSE(tree.getHash().empty());
}

TEST_F(TreeTest, SaveAndLoadTree) {
    // Build and save tree
    Tree tree = Tree::buildFromDirectory("test_files");
    tree.save();
    
    // Load tree
    Tree loadedTree = Tree::load(tree.getHash());
    
    // Check that hashes match
    EXPECT_EQ(loadedTree.getHash(), tree.getHash());
    
    // Check that entries match
    EXPECT_EQ(loadedTree.getEntries().size(), tree.getEntries().size());
}

TEST_F(TreeTest, FindBlobHash) {
    // Create and save blob first
    Blob blob("test_files/file1.txt");
    blob.save();
    
    // Build tree from directory
    Tree tree = Tree::buildFromDirectory("test_files");
    tree.save();
    
    // Find blob hash for the file using relative path
    std::string blobHash = tree.findBlobHash("file1.txt");
    EXPECT_FALSE(blobHash.empty());
    
    // Verify blob content
    Blob loadedBlob = Blob::load(blobHash);
    EXPECT_EQ(loadedBlob.getContent(), "Content 1");
}

TEST_F(TreeTest, FindNonExistentBlob) {
    // Build tree
    Tree tree = Tree::buildFromDirectory("test_files");
    
    // Try to find non-existent file
    std::string blobHash = tree.findBlobHash("nonexistent.txt");
    EXPECT_TRUE(blobHash.empty());
}

TEST_F(TreeTest, TreeHashConsistency) {
    // Build two trees from same directory
    Tree tree1 = Tree::buildFromDirectory("test_files");
    Tree tree2 = Tree::buildFromDirectory("test_files");
    
    // Check that hashes are the same
    EXPECT_EQ(tree1.getHash(), tree2.getHash());
}

TEST_F(TreeTest, LoadNonExistentTree) {
    // Try to load a tree that doesn't exist
    EXPECT_THROW(Tree::load("nonexistent_hash"), std::runtime_error);
}
