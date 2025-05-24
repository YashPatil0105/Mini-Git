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
    unordered_map<string, string> files;

public:
    Commit(const string& parent, const string& message, 
           const unordered_map<string,string>& files);

    void save() const;
    string getHash() const;
};