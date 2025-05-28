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
    string path = ".mini-git/trees/" + getHash();

    ofstream out(path);
    if(!out){
        cerr << "Failed to write tree to : " << path << endl;
        return ;
    }

    for (const auto& entry : entries){
        out << (entry.type == EntryType::BLOB ? "blob" : "tree") << " "
            << entry.name << " "
            << entry.hash << "\n";
    }

    out.close();
    cout << "Saved tree : " << path << endl;
}

Tree Tree::buildFromDirectory(const std::string& path) {
    Tree tree;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            Blob blob(entry.path().string());
            blob.save();
            tree.addEntry(EntryType::BLOB, filename, blob.getHash());
        } else if (entry.is_directory()) {
            string dirname = entry.path().filename().string();
            if (dirname == ".mini-git") continue; // skip repo dir
            Tree subtree = buildFromDirectory(entry.path().string());
            subtree.save();
            tree.addEntry(EntryType::TREE, dirname, subtree.getHash());
        }
    }
    return tree;
}