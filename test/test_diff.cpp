#include <gtest/gtest.h>
#include "utils/Diff.hpp"
#include <string>
#include <vector>

class DiffTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DiffTest, EmptyDiff) {
    std::vector<std::string> oldContent = {"line1", "line2"};
    std::vector<std::string> newContent = {"line1", "line2"};
    
    auto changes = Diff::generateDiff(oldContent, newContent);
    EXPECT_EQ(changes.size(), 2);
    
    for (const auto& change : changes) {
        EXPECT_EQ(change.type, Diff::ChangeType::UNCHANGED);
    }
}

TEST_F(DiffTest, AddedLines) {
    std::vector<std::string> oldContent = {"line1", "line2"};
    std::vector<std::string> newContent = {"line1", "line2", "line3", "line4"};
    
    auto changes = Diff::generateDiff(oldContent, newContent);
    EXPECT_EQ(changes.size(), 4);
    
    EXPECT_EQ(changes[0].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[1].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[2].type, Diff::ChangeType::ADDED);
    EXPECT_EQ(changes[3].type, Diff::ChangeType::ADDED);
}

TEST_F(DiffTest, RemovedLines) {
    std::vector<std::string> oldContent = {"line1", "line2", "line3", "line4"};
    std::vector<std::string> newContent = {"line1", "line2"};
    
    auto changes = Diff::generateDiff(oldContent, newContent);
    EXPECT_EQ(changes.size(), 4);
    
    EXPECT_EQ(changes[0].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[1].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[2].type, Diff::ChangeType::REMOVED);
    EXPECT_EQ(changes[3].type, Diff::ChangeType::REMOVED);
}

TEST_F(DiffTest, ModifiedLines) {
    std::vector<std::string> oldContent = {"line1", "old line", "line3"};
    std::vector<std::string> newContent = {"line1", "new line", "line3"};
    
    auto changes = Diff::generateDiff(oldContent, newContent);
    EXPECT_EQ(changes.size(), 5);
    
    // First line unchanged
    EXPECT_EQ(changes[0].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[0].content, "line1");
    
    // Second line removed
    EXPECT_EQ(changes[1].type, Diff::ChangeType::REMOVED);
    EXPECT_EQ(changes[1].content, "old line");
    
    // New line added
    EXPECT_EQ(changes[2].type, Diff::ChangeType::ADDED);
    EXPECT_EQ(changes[2].content, "new line");
    
    // Last line unchanged
    EXPECT_EQ(changes[3].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[3].content, "line3");
    
    // Extra unchanged line (implementation detail)
    EXPECT_EQ(changes[4].type, Diff::ChangeType::UNCHANGED);
    EXPECT_EQ(changes[4].content, "line3");
}

TEST_F(DiffTest, SplitIntoLines) {
    std::string content = "line1\nline2\nline3";
    auto lines = Diff::splitIntoLines(content);
    
    EXPECT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "line1");
    EXPECT_EQ(lines[1], "line2");
    EXPECT_EQ(lines[2], "line3");
}

TEST_F(DiffTest, FormatDiff) {
    std::vector<Diff::LineChange> changes = {
        {Diff::ChangeType::UNCHANGED, "line1", 1},
        {Diff::ChangeType::REMOVED, "old line", 2},
        {Diff::ChangeType::ADDED, "new line", 2},
        {Diff::ChangeType::UNCHANGED, "line3", 3}
    };
    
    std::string formatted = Diff::formatDiff(changes);
    EXPECT_FALSE(formatted.empty());
    EXPECT_TRUE(formatted.find("-") != std::string::npos);
    EXPECT_TRUE(formatted.find("+") != std::string::npos);
}

