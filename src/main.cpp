/// @file main.cpp
/// @author Juan
/// @brief Tournament simulator main program
/// @date 2025-11-04

#include "player_queue.h"
#include "player.h"
#include "bracket.h"
#include "text_utils.h"
#include "luck_checker.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

const int MAX_PLAYERS = 64;

/// Read players from file and fill queue
bool LoadPlayersFromFile(const std::string& filename,
                         PlayerQueue& queue) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir " << filename << std::endl;
        return false;
    }

    std::string name;
    int count = 0;

    while (std::getline(file, name) && count < MAX_PLAYERS) {
        /// Skip empty lines
        if (name.empty()) {
            continue;
        }

        Player player(name);
        if (queue.Enqueue(player)) {
            count++;
        } else {
            std::cerr << "Advertencia: Cola llena, jugador "
                      << name << " ignorado" << std::endl;
            break;
        }
    }

    file.close();

    if (count == 0) {
        std::cerr << "Error: No se cargaron jugadores" << std::endl;
        return false;
    }

    /// Complete to next power of 2 with BYE
    int next_power = 1;
    while (next_power < count) {
        next_power *= 2;
    }

    int byes_needed = next_power - count;
    for (int i = 0; i < byes_needed; i++) {
        queue.Enqueue(Player("BYE"));
    }

    std::cout << "Cargados: " << count << " jugadores" << std::endl;
    std::cout << "Agregados: " << byes_needed << " BYE" << std::endl;
    std::cout << "Total: " << queue.Size() << " participantes" << std::endl;

    return true;
}

int main() {
    /// THE SACRED LUCK DOG MUST BE VALIDATED FIRST
    if (!ValidateLuckDog()) {
        ShowCurseMessage();
        std::cout << "\nPress any key to accept your fate...\n";
        std::cin.get();
        return 666; // The number of the beast, obviously
    }

    ClearScreen();
    SetUTF8Encoding();

    /// Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << GREEN << "MINI SIMULADOR DE TORNEO" << RESET << std::endl;
    std::cout << std::endl;

    /// Create queue
    PlayerQueue queue(MAX_PLAYERS);

    /// Load players
    std::cout << BOLD << "CARGA DE JUGADORES" << RESET << std::endl;
    if (!LoadPlayersFromFile("jugadores.txt", queue)) {
        return 1;
    }

    /// Show queue state
    std::cout << "\n" << BOLD << "REGISTRO (COLA)" << RESET << std::endl;
    queue.Print();

    /// Build bracket
    Bracket bracket;
    bracket.BuildFromQueue(queue);

    /// Simulate tournament
    bracket.Simulate();

    /// Show champion
    bracket.PrintRounds();

    std::cout << "\n" << BOLD << "FIN DEL TORNEO" << RESET << std::endl;
    std::cout << "Press any key to continue...";
    std::cin.get();  // Espera a que el usuario presione Enter
    return 0;
}