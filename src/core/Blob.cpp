#include "core/Blob.hpp"
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

Blob::Blob(const string& filePath){
    ifstream file(filePath);
    stringstream ss;
    ss << file.rdbuf();
    content = ss.str();
    hash = to_string(std::hash<string>{}(content));
}

const string& Blob::getHash() const{
    return hash;
}

const string& Blob::getContent() const {
    return content;
}