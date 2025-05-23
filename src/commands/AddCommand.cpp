#include "commands/AddCommand.hpp"
#include "core/Blob.hpp"
#include "repository/StagingArea.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

static StagingArea staging; 

AddCommand::AddCommand(const string& file) : filename(file) {}

void AddCommand::execute(){
    if(!fs::exists(filename)){
        cout << "File does not exists" << filename << endl;
        return;
    }

    Blob blob(filename);
    string hash = blob.getHash();

    string objPath = ".minigit/objects/" + hash;
    ofstream out(objPath);
    out << blob.getContent();
    out.close();

    staging.add(filename, hash);

    cout << "Added " << filename << " to staging area.\n";
}