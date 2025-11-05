/// @file luck_checker.cpp
/// @author Juan
/// @brief Implementation of the sacred luck dog validator
/// @date 2025-11-04

#include "luck_checker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <text_utils.h>

const std::string LUCK_DOG_FILE = "the_luck_dog.txt";

/// The sacred text that must remain unchanged
const std::string SACRED_HEADER =
    "IF YOU REMOVE THIS FILE OR EVEN MODIFY THE CONTENT OF IT, "
    "EVERYTHING WILL BREAK!";

bool ValidateLuckDog() {
    std::ifstream file(LUCK_DOG_FILE);

    /// File doesn't exist - THE CURSE IS REAL
    if (!file.is_open()) {
        return false;
    }

    /// Read entire file content
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    file.close();

    /// Check if the sacred header is present at the beginning
    if (content.find(SACRED_HEADER) != 0) {
        return false;
    }

    /// Additional check: file must have the dog ASCII art
    /// We check for specific patterns in the art
    if (content.find("@@@@@@@") == std::string::npos ||
        content.find("%%%%%%") == std::string::npos ||
        content.find("####") == std::string::npos) {
        return false;
    }

    /// File must be at least 2000 characters (header + dog art)
    if (content.length() < 2000) {
        return false;
    }

    return true;
}

void ShowCurseMessage() {
    SetUTF8Encoding();

    std::cout << "\n\033[31m\033[1m";
    std::cout << "╔═══════════════════════════════════════════════╗\n";
    std::cout << "║                                               ║\n";
    std::cout << "║         ⚠️  THE LUCK DOG HAS FLED ⚠️            ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "║  You have disturbed the sacred luck dog!      ║\n";
    std::cout << "║  the_luck_dog.txt is missing or modified!     ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "║  Your compilation privileges have been        ║\n";
    std::cout << "║  REVOKED until you restore the file!          ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "║  The file must contain:                       ║\n";
    std::cout << "║  1. The sacred warning message                ║\n";
    std::cout << "║  2. The complete ASCII art dog                ║\n";
    std::cout << "║  3. EXACTLY as provided in the repo           ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "║          🐕 WOOF WOOF (angrily) 🐕            ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "║  Restore the file from the repository and     ║\n";
    std::cout << "║  try again. DO NOT modify it!                 ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "║  May the Luck Dog have mercy on us all...     ║\n";
    std::cout << "║                                               ║\n";
    std::cout << "╚═══════════════════════════════════════════════╝\n";
    std::cout << "\033[0m\n";
}