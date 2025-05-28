#pragma once
#include <string>

using namespace std;

class Blob {
    string content;
    string hash;

public:
    Blob(const string& filepath);
    const string& getHash() const;
    const string& getContent() const;
    void save() const;  
};
