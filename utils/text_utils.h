/// @file text_utils.h
/// @author Juan
/// @brief Text formatting and display utilities
/// @date 2025-11-04

#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

/// ANSI color codes
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"

/// Clear screen function
void ClearScreen();
void SetUTF8Encoding();

/// Display loading message with animated dots
void MsgLoading(const std::string& message, int cycles,
                bool clear_after = false);

#endif