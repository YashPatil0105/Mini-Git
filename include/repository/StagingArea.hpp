#pragma once
#include <unordered_map>
#include <string>
using namespace std;

class StagingArea {
     unordered_map<string,string> staged;

public:
    void add(const string& filename, const string& hash);
    const unordered_map<string, string>& getStagedFiles() const;
    
};