#include "commands/InitCommand.hpp"
#include "commands/AddCommand.hpp"

int main() {
    InitCommand init;
    init.execute();

    AddCommand add("example.txt");
    add.execute();

    return 0;
}
