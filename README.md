# Mini-Git

A lightweight, educational implementation of Git version control system in C++. This project demonstrates core Git concepts and data structures while providing a functional subset of Git commands.

## Features

### Core Commands
- `init` - Initialize a new repository
- `add` - Stage files for commit
- `commit` - Create a new commit with staged changes
- `status` - Show working tree status
- `diff` - Show changes between working tree and last commit
- `branch` - Create and manage branches

### Data Structures
- **Blob**: Stores file contents with SHA-1 hash
- **Tree**: Implements Merkle tree for directory structure
- **Commit**: Tracks commit metadata and parent relationships
- **StagingArea**: Manages staged changes

### Advanced Features
- Merkle Tree implementation for efficient change tracking
- LCS-based diff algorithm for change detection
- Branch management system
- SHA-1 hashing for content addressing

## Installation

### Prerequisites
- C++17 compatible compiler
- CMake (version 3.10 or higher)
- Git (for cloning)

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/yourusername/mini-git.git
cd mini-git

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build .
```

## Usage

### Basic Workflow
```bash
# Initialize a new repository
mini-git init

# Stage a file
mini-git add filename.txt

# Create a commit
mini-git commit "Initial commit"

# Check status
mini-git status

# View changes
mini-git diff filename.txt

# Create a new branch
mini-git branch new-branch -c
```

## Project Structure

```
mini-git/
├── include/                 # Header files
│   ├── cli/                # Command-line interface
│   ├── commands/           # Git command implementations
│   ├── core/               # Core data structures
│   └── utils/              # Utility functions
├── src/                    # Source files
│   ├── cli/                # CLI implementation
│   ├── commands/           # Command implementations
│   ├── core/               # Core implementations
│   └── utils/              # Utility implementations
├── test/                   # Test files
├── CMakeLists.txt          # Build configuration
└── README.md              # This file
```

## Architecture

### Core Components

1. **Blob**
   - Stores file contents
   - Generates SHA-1 hash for content addressing
   - Handles file I/O operations

2. **Tree**
   - Implements Merkle tree structure
   - Tracks directory hierarchy
   - Manages blob and subtree references

3. **Commit**
   - Stores commit metadata
   - Maintains parent commit references
   - Links to root tree

4. **StagingArea**
   - Tracks staged changes
   - Manages file status
   - Prepares commit data

### Command Implementation

Each Git command is implemented as a separate class inheriting from the `Command` base class:
- `InitCommand`: Repository initialization
- `AddCommand`: File staging
- `CommitCommand`: Commit creation
- `StatusCommand`: Status reporting
- `DiffCommand`: Change detection
- `BranchCommand`: Branch management

## Testing

The project includes comprehensive unit tests using Google Test framework:

```bash
# Run all tests
./mini_git_tests
```

Test coverage includes:
- Blob operations
- Tree operations
- Commit operations
- Diff algorithm
- Command functionality

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Inspired by the Git version control system
- Uses Google Test for testing
- Implements concepts from the Git internals documentation
