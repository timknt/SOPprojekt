# Greppy - A Powerful Search Tool

## Description
Greppy is a powerful command-line tool for searching text in files and directories. It supports various options to control the search, including recursive search, case insensitivity, count mode, and more.

## Features
- Support for recursive search
- Case-insensitive mode
- Configurable maximum number of matches
- Count occurrences
- Output in various formats

## Installation
### Prerequisites
- C compiler (e.g., GCC or Clang)
- CMake (for building the project)

### Build Instructions
1. Clone the repository:
   ```sh
   git clone <REPOSITORY-URL>
   cd greppy
   ```
2. Create a CMake build:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. The program is now executable:
   ```sh
   ./greppy <search_term> <file/directory>
   ```

## Usage
The program can be executed with various options:
```sh
./greppy [OPTIONS] <SEARCH_TERM> <FILE/DIRECTORY>
```

### Important Options
- `-r` : Recursive search in subdirectories
- `-i` : Case-insensitive search
- `-c` : Count occurrences
- `-m <N>` : Set the maximum number of matches
- `-q` : Suppress output (only exit code)

### Example Commands
- Search for "error" in `log.txt`:
  ```sh
  ./greppy error log.txt
  ```
- Recursive search for "TODO" in `src/`:
  ```sh
  ./greppy -r TODO src/
  ```
- Count occurrences of "debug" in `log.txt`:
  ```sh
  ./greppy -c debug log.txt
  ```

## Authors
Developed by Adrian Stelter, Tim Knüttel, and Jakob Hämmelmann.

