#include "core/Blob.hpp"
#include <fstream>
#include <sstream>
#include <functional>
#include <filesystem>
#include <iostream>
#include "utils/sha1.hpp"

using namespace std;
namespace fs = std::filesystem;

Blob::Blob(const string& filePath) {
    ifstream file(filePath); // optionally use ios::binary
    stringstream ss;
    ss << file.rdbuf();
    content = ss.str();
    hash = SHA1::from_string(content);
}

const string& Blob::getHash() const {
    return hash;
}

const string& Blob::getContent() const {
    return content;
}

void Blob::save() const {
    fs::create_directories(".mini-git/objects");
    string blobPath = ".mini-git/objects/" + hash;
    
    ofstream out(blobPath, std::ios::binary); // optional: ios::binary
    if (!out) {
        cerr << "Failed to write blob to: " << blobPath << "\n";
        return;
    }
    out << content;
    out.close();

    cout << "Saved blob: " << blobPath << endl;
}
