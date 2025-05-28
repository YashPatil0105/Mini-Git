// #include <iostream>
// #include <string>
// #include "commands/AddCommand.hpp"
// #include "commands/CommitCommand.hpp"
// #include "commands/InitCommand.hpp"
// #include "repository/StagingArea.hpp"
// #include "commands/StatusCommand.hpp"

// using namespace std;

// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         cout << "Usage: mini-git <command> [args]\n";
//         return 1;
//     }

//     StagingArea staging;

//     string command = argv[1];
//     if (command == "init") {
//         InitCommand init;
//         init.execute();
//     }
//     else if (command == "add") {
//         if (argc < 3) {
//             cout << "Please specify a file to add.\n";
//             return 1;
//         }
//         AddCommand add(argv[2], staging);
//         add.execute();
//     }
//     else if (command == "commit") {
//         if (argc < 3) {
//             cout << "Please provide a commit message.\n";
//             return 1;
//         }
//         CommitCommand commit(argv[2]);
//         commit.execute();
//     }
//     else if (command == "status"){
//         StatusCommand status(staging);
//         status.execute();
//     }
//     else {
//         cout << "Unknown command: " << command << "\n";
//     }


//     return 0;
// }

#include <iostream>
#include <memory>
#include "commands/Command.hpp"
#include "cli/CliParser.hpp"
#include "repository/StagingArea.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: mini-git <command> [args]\n";
        return 1;
    }

    shared_ptr<StagingArea> staging = make_shared<StagingArea>();
    unique_ptr<Command> cmd = CliParser::parse(argc, argv, staging);

    if (!cmd) {
        cout << "Invalid or incomplete command.\n";
        return 1;
    }

    cmd->execute();

    return 0;
}

