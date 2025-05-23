#include "repository/StagingArea.hpp"

using namespace std;

void StagingArea::add(const string& filename, const string& hash){
    staged[filename] = hash;
}

const unordered_map<string,string>& StagingArea::getStagedFiles() const{
    return staged;
}