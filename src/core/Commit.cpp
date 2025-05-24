#include "core/Commit.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include <functional>

namespace fs = std::filesystem;

Commit::Commit(const string& parentHash, const string& msg,
               const unordered_map<string, string>& fileMap) 
               
               : parent(parentHash) , message(msg), timestamp(time(nullptr)), files(fileMap)
               {
                    stringstream ss;
                    ss << parent << message << timestamp;
                    hash = std::to_string(std::hash<std::string>{}(ss.str()));
               }


void Commit::save() const{
    string path = ".minigit/objects/" + hash;
    ofstream out(path);
    out << "commit " << hash << "\n";
    out << "parent " << parent << "\n";
    out << "date " << timestamp << "\n";
    out << "message " << message << "\n\n";

    for(const auto& [filename, blobHash] : files){
        out << filename << " " << blobHash << "\n";
    } 
    out.close();
}

string Commit::getHash() const{
    return hash;
}