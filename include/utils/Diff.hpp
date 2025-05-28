#pragma once
#include <string>
#include <vector>
#include <utility>

class Diff {
public:
    // Represents a line change in a file
    enum class ChangeType {
        ADDED,
        REMOVED,
        UNCHANGED
    };

    struct LineChange {
        ChangeType type;
        std::string content;
        int lineNumber;
    };

    // Compute the LCS between two strings
    static std::vector<std::string> computeLCS(const std::vector<std::string>& a, 
                                             const std::vector<std::string>& b);

    // Generate diff between two files
    static std::vector<LineChange> generateDiff(const std::vector<std::string>& oldContent,
                                              const std::vector<std::string>& newContent);

    // Format diff output for display
    static std::string formatDiff(const std::vector<LineChange>& changes);

    // Helper to split string into lines
    static std::vector<std::string> splitIntoLines(const std::string& content);

private:
    // No private members needed
}; 