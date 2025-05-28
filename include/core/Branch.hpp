#pragma once
#include <string>

class Branch {
public:
    Branch(const std::string& name, const std::string& commitHash);
    const std::string& getName() const;
    const std::string& getCommitHash() const;
    void setCommitHash(const std::string& hash);
    void save() const;
    static Branch load(const std::string& name);

private:
    std::string name;
    std::string commitHash;
}; 