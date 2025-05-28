#include "core/Blob.hpp"
#include <iostream>
#include <fstream>

int main() {
    std::ofstream out("sample_blob.txt");
    out << "This is a blob content.";
    out.close();

    Blob blob("sample_blob.txt");

    std::cout << "Content:\n" << blob.getContent() << "\n";
    std::cout << "Hash:\n" << blob.getHash() << "\n";

    blob.save();  // <--- Save blob object here

    std::cout << "Blob saved at: .mini-git/blob/" << blob.getHash() << std::endl;

    return 0;
}
