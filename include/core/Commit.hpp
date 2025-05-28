// #pragma once
// #include <string>
// #include <ctime>
// #include <unordered_map>

// using namespace std;

// class Commit {
//     string hash;
//     string parent;
//     string message;
//     time_t timestamp;
//     unordered_map<string, string> files;

// public:
//     Commit(const string& parent, const string& message, 
//            const unordered_map<string,string>& files);

//     void save() const;
//     string getHash() const;
// };

#pragma once
#include <string>
#include <ctime>
#include <unordered_map>

using namespace std;

class Commit {
    string hash;
    string parent;
    string message;
    time_t timestamp;
    string treeHash; // root tree hash

public:
    Commit(const string& parent, const string& message, const string& treeHash);

    void save() const;
    static Commit load(const string& hash);

    string getHash() const;
    string getParent() const;
    string getMessage() const;
    time_t getTimestamp() const;
    string getTreeHash() const;
};
