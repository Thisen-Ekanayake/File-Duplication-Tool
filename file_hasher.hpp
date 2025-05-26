#ifndef FILE_HASHER_HPP
#define FILE_HASHER_HPP

#include <string>


//  computes sha-256 hash of the file at file_path and returns it as a hex  string
std::string compute_sha256(const std::string& file_path);

#endif  // FILE_HASHER_HPP