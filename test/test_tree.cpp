#include "core/Tree.hpp"
#include "core/Blob.hpp"
#include <iostream>
using namespace std;

int main() {
    Blob blob1("sample1.txt");
    Blob blob2("sample2.txt");

    Tree tree;
    tree.addEntry(EntryType::BLOB, "sample1.txt", blob1.getHash());
    tree.addEntry(EntryType::BLOB, "sample2.txt", blob2.getHash());

    tree.save();
    cout << "Tree hash: " << tree.getHash() << endl;

    for (const auto& entry : tree.getEntries()) {
        string entryTypeStr = (entry.type == EntryType::BLOB) ? "blob" : "tree";
        cout << entryTypeStr << " " << entry.hash << " " << entry.name << endl;
    }

    return 0;
}
