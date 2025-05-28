#pragma once 
#include <string>
#include <vector>

using namespace std;

enum class EntryType{
    BLOB,
    TREE
};

struct TreeEntry {
    EntryType type;
    string name;
    string hash;

    TreeEntry(EntryType t, const string& n , const string& h) : type(t) , name(n), hash(h) {}

};

class Tree {
    vector<TreeEntry> entries;
    string hash;

public: 
    void addEntry(EntryType type, const string& name, const string& hash);
    void save(); //saves to .mini-git/tree/
    const string& getHash(); // computes hash if needed
    const vector<TreeEntry>& getEntries() const;

    static Tree buildFromDirectory(const std::string& path);
};