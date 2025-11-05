/// @file text_utils.cpp
/// @author Juan
/// @brief Implementation of text utilities
/// @date 2025-11-04

#include "text_utils.h"

#ifdef _WIN32
#include <windows.h>
#endif

void SetUTF8Encoding() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

void ClearScreen() {
    #ifdef _WIN32
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        DWORD count;
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(console, &csbi)) {
            DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
            FillConsoleOutputCharacter(console, ' ', cells, coord, &count);
            FillConsoleOutputAttribute(console, csbi.wAttributes, cells,
                                       coord, &count);
            SetConsoleCursorPosition(console, coord);
        }
    #else
        std::cout << "\033[2J\033[1;1H";
        std::cout.flush();
    #endif
}

void MsgLoading(const std::string& message, int cycles, bool clear_after) {
    for (int i = 0; i < cycles; ++i) {
        std::cout << CYAN << BOLD << "[Status]: " << RESET << message;

        for (int j = 0; j < 3; ++j) {
            std::cout << ".";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }

        /// Clear line
        std::cout << "\r" << std::string(50, ' ') << "\r";
        std::cout.flush();
    }

    if (clear_after) {
        ClearScreen();
    }
}