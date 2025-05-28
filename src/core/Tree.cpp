#include "core/Tree.hpp"
#include "core/Blob.hpp"
#include <sstream>
#include <fstream>
#include <functional>
#include <filesystem>
#include <iostream>
#include "utils/sha1.hpp"

using namespace std;
namespace fs = std::filesystem;

void Tree::addEntry(EntryType type, const string& name, const string& hash){
    entries.emplace_back(type, name, hash);
}

const string& Tree::getHash(){
    if(!hash.empty()) return hash;

    stringstream ss;
    for (const auto& entry : entries){
        ss << (entry.type == EntryType::BLOB ? "blob" : "tree") << " "
           << entry.name << " "
           << entry.hash << "\n";
    }

    hash = SHA1::from_string(ss.str());
    return hash;
}

const vector<TreeEntry>& Tree::getEntries() const {
    return entries;
}

void Tree::save(){
    fs::create_directories(".mini-git/trees");
    string treePath = ".mini-git/trees/" + getHash();
    
    ofstream out(treePath);
    if (!out) {
        throw runtime_error("Failed to write tree to: " + treePath);
    }
    
    for (const auto& entry : entries){
        out << (entry.type == EntryType::BLOB ? "blob" : "tree") << " "
            << entry.name << " "
            << entry.hash << "\n";
    }
    out.close();
}

string Tree::findBlobHash(const string& filePath) const {
    // Split path into components
    vector<string> components;
    stringstream ss(filePath);
    string component;
    while (getline(ss, component, '/')) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }

    // Start from root tree
    const Tree* currentTree = this;
    vector<Tree> loadedTrees; // Keep loaded trees alive

    // Traverse the tree
    for (size_t i = 0; i < components.size(); i++) {
        const string& component = components[i];
        bool found = false;

        for (const auto& entry : currentTree->entries) {
            if (entry.name == component) {
                if (i == components.size() - 1) {
                    // Last component - should be a blob
                    if (entry.type == EntryType::BLOB) {
                        return entry.hash;
                    }
                    return ""; // Not a blob
                } else {
                    // Not last component - should be a tree
                    if (entry.type == EntryType::TREE) {
                        loadedTrees.push_back(Tree::load(entry.hash));
                        currentTree = &loadedTrees.back();
                        found = true;
                        break;
                    }
                    return ""; // Not a tree
                }
            }
        }

        if (!found) {
            return ""; // Component not found
        }
    }

    return ""; // Path not found
}

Tree Tree::load(const string& hash) {
    string treePath = ".mini-git/trees/" + hash;
    ifstream in(treePath);
    if (!in) {
        throw runtime_error("Tree not found: " + hash);
    }

    Tree tree;
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string type, name, entryHash;
        ss >> type >> name >> entryHash;
        
        EntryType entryType = (type == "blob") ? EntryType::BLOB : EntryType::TREE;
        tree.addEntry(entryType, name, entryHash);
    }

    return tree;
}

Tree Tree::buildFromDirectory(const string& path) {
    Tree tree;
    
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().filename() == ".mini-git") continue;
        
        if (entry.is_regular_file()) {
            Blob blob(entry.path().string());
            blob.save();
            tree.addEntry(EntryType::BLOB, entry.path().filename().string(), blob.getHash());
        }
        else if (entry.is_directory()) {
            Tree subtree = buildFromDirectory(entry.path().string());
            subtree.save();
            tree.addEntry(EntryType::TREE, entry.path().filename().string(), subtree.getHash());
        }
    }
    
    return tree;
}