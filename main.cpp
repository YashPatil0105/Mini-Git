#include <iostream>
#include <vector>
#include <map>

int main() {
    auto name = "MiniGit";
    std::cout << "Hello, " << name << "!\n";

    std::map<std::string, int> counters{{"add", 1}, {"commit", 0}};
    for (const auto& [cmd, count] : counters) {
        std::cout << cmd << " => " << count << "\n";
    }

    return 0;
}
