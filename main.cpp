#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include "file_hasher.hpp"

namespace fs = std::filesystem;

// function to scan directory and hash files
void scan_and_detect_duplicates(const std::string& folder_path) {
    std::unordered_map<std::string, std::vector<std::string>> hash_to_files;

    for (const auto& entry : fs::recursive_directory_iterator(folder_path)) {
        if (fs::is_regular_file(entry.path())) {
            std::string file_path = entry.path().string();
            std::string hash = compute_sha256(file_path);

            if (hash.empty()) {
                std::cerr << "Could not hash file: " << file_path << "\n";
                continue;
            }

            hash_to_files[hash].push_back(file_path);
        }
    }
    std::cout<< "\n Duplicate files:\n";
    int group_num = 1;
    for (const auto& [hash, paths] : hash_to_files) {
        if (paths.size() > 1) {
            std::cout << "\nGroup " << group_num++ << " (Hash: " << hash << "):\n";
            for (const std::string& path : paths) {
                std::cout << " - " << path << '\n';
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./main <folder_path>\n";
        return 1;
    }

    std::string folder_path = argv[1];
    if (!fs::exists(folder_path) || !fs::is_directory(folder_path)) {
        std::cerr << "Invalid folder path.\n";
        return 1;
    }

    scan_and_detect_duplicates(folder_path);

    return 0;
}