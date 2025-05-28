#include "repository/StagingArea.hpp"
#include <fstream>
#include <filesystem>
#include <iostream> 

namespace fs = std::filesystem;
using namespace std;


StagingArea::StagingArea(){
    load();
}
void StagingArea::add(const string& filename, const string& hash){
    staged[filename] = hash;
    save();
}

void StagingArea::clear() {
    staged.clear();
    save();
}

const unordered_map<string,string>& StagingArea::getStagedFiles() const{
    return staged;
}


void StagingArea::save() const {
    fs::create_directories(".mini-git"); 
    std::ofstream out(indexPath);
    if (!out) {
        return;
    }
    for (const auto& [file, hash] : staged) {
        out << file << " " << hash << "\n";
    }
}

// void StagingArea::load() {
//     staged.clear();
//     if (!fs::exists(indexPath)) return;

//     std::ifstream in(indexPath);
//     std::string file, hash;
//     while (in >> file >> hash) {
//         staged[file] = hash;
//     }
// }

void StagingArea::load() {
    staged.clear();
    if (!fs::exists(indexPath)) {
        return;
    }

    std::ifstream in(indexPath);
    std::string file, hash;
    while (in >> file >> hash) {
        staged[file] = hash;
    }
}
