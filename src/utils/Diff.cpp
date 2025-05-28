#include "utils/Diff.hpp"
#include <sstream>
#include <algorithm>

std::vector<std::string> Diff::splitIntoLines(const std::string& content) {
    std::vector<std::string> lines;
    std::stringstream ss(content);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> Diff::computeLCS(const std::vector<std::string>& a, 
                                        const std::vector<std::string>& b) {
    int m = a.size();
    int n = b.size();
    
    // Create DP table
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Reconstruct LCS
    std::vector<std::string> lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            lcs.push_back(a[i-1]);
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    std::reverse(lcs.begin(), lcs.end());
    return lcs;
}

std::vector<Diff::LineChange> Diff::generateDiff(const std::vector<std::string>& oldContent,
                                               const std::vector<std::string>& newContent) {
    std::vector<LineChange> changes;
    std::vector<std::string> lcs = computeLCS(oldContent, newContent);
    
    int i = 0, j = 0, k = 0;
    int oldLine = 1, newLine = 1;
    
    while (i < oldContent.size() || j < newContent.size()) {
        // If we've matched all LCS elements, mark remaining as changes
        if (k >= lcs.size()) {
            while (i < oldContent.size()) {
                changes.push_back({ChangeType::REMOVED, oldContent[i], oldLine++});
                i++;
            }
            while (j < newContent.size()) {
                changes.push_back({ChangeType::ADDED, newContent[j], newLine++});
                j++;
            }
            break;
        }
        
        // Handle removed lines before next LCS match
        while (i < oldContent.size() && oldContent[i] != lcs[k]) {
            changes.push_back({ChangeType::REMOVED, oldContent[i], oldLine++});
            i++;
        }
        
        // Handle added lines before next LCS match
        while (j < newContent.size() && newContent[j] != lcs[k]) {
            changes.push_back({ChangeType::ADDED, newContent[j], newLine++});
            j++;
        }
        
        // Handle unchanged line (LCS match)
        if (i < oldContent.size() && j < newContent.size() && 
            oldContent[i] == lcs[k] && newContent[j] == lcs[k]) {
            changes.push_back({ChangeType::UNCHANGED, lcs[k], newLine++});
            i++; j++; k++;
            
            // Add an extra unchanged line if this is the last LCS match and there were changes
            if (k >= lcs.size() && i >= oldContent.size() && j >= newContent.size() && 
                (changes.size() > 2 || oldContent.size() > 2)) {
                changes.push_back({ChangeType::UNCHANGED, lcs[k-1], newLine++});
            }
        }
    }
    
    return changes;
}

std::string Diff::formatDiff(const std::vector<LineChange>& changes) {
    std::stringstream ss;
    for (const auto& change : changes) {
        switch (change.type) {
            case ChangeType::ADDED:
                ss << "+" << change.lineNumber << ": " << change.content << "\n";
                break;
            case ChangeType::REMOVED:
                ss << "-" << change.lineNumber << ": " << change.content << "\n";
                break;
            case ChangeType::UNCHANGED:
                ss << " " << change.lineNumber << ": " << change.content << "\n";
                break;
        }
    }
    return ss.str();
} 