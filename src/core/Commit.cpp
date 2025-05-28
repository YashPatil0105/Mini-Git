// #include "core/Commit.hpp"
// #include <fstream>
// #include <filesystem>
// #include <sstream>
// #include <ctime>
// #include <functional>

// namespace fs = std::filesystem;

// Commit::Commit(const string& parentHash, const string& msg,
//                const unordered_map<string, string>& fileMap) 
               
//                : parent(parentHash) , message(msg), timestamp(time(nullptr)), files(fileMap)
//                {
//                     stringstream ss;
//                     ss << parent << message << timestamp;
//                     hash = std::to_string(std::hash<std::string>{}(ss.str()));
//                }


// void Commit::save() const{
//     string path = ".minigit/objects/" + hash;
//     ofstream out(path);
//     out << "commit " << hash << "\n";
//     out << "parent " << parent << "\n";
//     out << "date " << timestamp << "\n";
//     out << "message " << message << "\n\n";

//     for(const auto& [filename, blobHash] : files){
//         out << filename << " " << blobHash << "\n";
//     } 
//     out.close();
// }

// string Commit::getHash() const{
//     return hash;
// }

#include "core/Commit.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include "utils/sha1.hpp"

namespace fs = std::filesystem;

Commit::Commit(const string& parentHash, const string& msg, const string& treeHash)
    : parent(parentHash), message(msg), timestamp(time(nullptr)), treeHash(treeHash)
{
    stringstream ss;
    ss << parent << message << timestamp << treeHash;
    hash = SHA1::from_string(ss.str());
}

void Commit::save() const {
    string path = ".mini-git/objects/" + hash;
    ofstream out(path);
    out << "commit " << hash << "\n";
    out << "parent " << parent << "\n";
    out << "date " << timestamp << "\n";
    out << "tree " << treeHash << "\n";
    out << "message " << message << "\n";
    out.close();
}

Commit Commit::load(const string& hash) {
    string path = ".mini-git/objects/" + hash;
    ifstream in(path);
    if (!in) throw runtime_error("Commit file not found: " + hash);

    string line, keyword;
    string parent, message, treeHash;
    time_t timestamp = 0;

    getline(in, line); // skip 'commit <hash>'
    getline(in, line);
    if (line.rfind("parent ", 0) == 0)
        parent = line.substr(7);
    getline(in, line);
    if (line.rfind("date ", 0) == 0)
        timestamp = stol(line.substr(5));
    getline(in, line);
    if (line.rfind("tree ", 0) == 0)
        treeHash = line.substr(5);
    getline(in, line); // message line
    if (line.rfind("message ", 0) == 0)
        message = line.substr(8);

    Commit c(parent, message, treeHash);
    c.timestamp = timestamp;
    c.hash = hash; // manually set same hash
    return c;
}

string Commit::getHash() const {
    return hash;
}

string Commit::getParent() const {
    return parent;
}

string Commit::getMessage() const {
    return message;
}

time_t Commit::getTimestamp() const {
    return timestamp;
}

string Commit::getTreeHash() const {
    return treeHash;
}
