#include <iostream>
#include "file_hasher.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    std::string file_path = argv[1];
    std::string hash = compute_sha256(file_path);

    if (hash.empty()) {
        std::cerr << "Error: Unable to open file or compute hash.\n";
        return 1;
    }

    std::cout << "SHA-256 hash of \"" << file_path << "\":\n" << hash << "\n";
    return 0;
}