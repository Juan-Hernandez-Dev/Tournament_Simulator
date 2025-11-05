/// @file player.h
/// @author Juan
/// @brief Player structure definition
/// @date 2025-11-04

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player {
    std::string name;

    Player() : name("") {}
    Player(const std::string& n) : name(n) {}

    bool IsBye() const {
        return name == "BYE";
    }

    bool IsEmpty() const {
        return name.empty();
    }
};

#endif