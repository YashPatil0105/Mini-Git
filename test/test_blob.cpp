#include <gtest/gtest.h>
#include "core/Blob.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class BlobTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test directory
        fs::create_directories("test_files");
    }

    void TearDown() override {
        // Clean up test files
        fs::remove_all("test_files");
        fs::remove_all(".mini-git");
    }
};

TEST_F(BlobTest, CreateBlobFromFile) {
    // Create a test file
    std::string content = "Hello, World!";
    std::ofstream file("test_files/test.txt");
    file << content;
    file.close();

    // Create blob from file
    Blob blob("test_files/test.txt");

    // Check content and hash
    EXPECT_EQ(blob.getContent(), content);
    EXPECT_FALSE(blob.getHash().empty());
}

TEST_F(BlobTest, SaveAndLoadBlob) {
    // Create a test file
    std::string content = "Test content";
    std::ofstream file("test_files/test.txt");
    file << content;
    file.close();

    // Create and save blob
    Blob blob("test_files/test.txt");
    blob.save();

    // Load blob
    Blob loadedBlob = Blob::load(blob.getHash());

    // Check content and hash
    EXPECT_EQ(loadedBlob.getContent(), content);
    EXPECT_EQ(loadedBlob.getHash(), blob.getHash());
}

TEST_F(BlobTest, BlobHashConsistency) {
    // Create a test file
    std::string content = "Same content";
    std::ofstream file1("test_files/test1.txt");
    std::ofstream file2("test_files/test2.txt");
    file1 << content;
    file2 << content;
    file1.close();
    file2.close();

    // Create two blobs with same content
    Blob blob1("test_files/test1.txt");
    Blob blob2("test_files/test2.txt");

    // Check that hashes are the same
    EXPECT_EQ(blob1.getHash(), blob2.getHash());
}

TEST_F(BlobTest, BlobHashUniqueness) {
    // Create two test files with different content
    std::ofstream file1("test_files/test1.txt");
    std::ofstream file2("test_files/test2.txt");
    file1 << "Content 1";
    file2 << "Content 2";
    file1.close();
    file2.close();

    // Create two blobs with different content
    Blob blob1("test_files/test1.txt");
    Blob blob2("test_files/test2.txt");

    // Check that hashes are different
    EXPECT_NE(blob1.getHash(), blob2.getHash());
}

TEST_F(BlobTest, LoadNonExistentBlob) {
    // Try to load a blob that doesn't exist
    EXPECT_THROW(Blob::load("nonexistent_hash"), std::runtime_error);
}
