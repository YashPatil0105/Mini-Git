#pragma once
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

class Blob {
    string content;
    string hash;

public:
    Blob(const string& filepath);
    const string& getHash() const;
    const string& getContent() const;
    void save() const;
    static Blob load(const string& hash);

private:
    // Private default constructor for use in load()
    Blob() = default;
};
