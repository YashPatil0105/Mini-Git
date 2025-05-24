#pragma once
#include <unordered_map>
#include <string>
using namespace std;

class StagingArea {
     unordered_map<string,string> staged;
     const string indexPath = ".minigit/index";

public:
    StagingArea();
    void add(const string& filename, const string& hash);
    const unordered_map<string, string>& getStagedFiles() const;
    void clear();
    void save() const;
    void load();
    
};