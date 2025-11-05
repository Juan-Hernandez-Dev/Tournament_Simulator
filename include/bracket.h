/// @file bracket.h
/// @author Juan
/// @brief Binary tree bracket for tournament simulation
/// @date 2025-11-04

#ifndef BRACKET_H
#define BRACKET_H

#include "player.h"
#include "player_queue.h"
#include <vector>

struct Node {
    Player value;
    Node* left;
    Node* right;
    int level;

    Node() : value(), left(nullptr), right(nullptr), level(0) {}
    Node(const Player& p, int lvl = 0)
        : value(p), left(nullptr), right(nullptr), level(lvl) {}
};

class Bracket {
  public:
    Bracket();
    ~Bracket();

    void BuildFromQueue(PlayerQueue& queue);
    void Simulate();
    void PrintRounds() const;
    Player Champion() const;

  private:
    Node* root_;
    int total_levels_;
    std::vector<std::vector<Node*>> rounds_;

    void DestroyTree(Node* node);
    void BuildCompleteTree(PlayerQueue& queue);
    void CollectByLevels();
    void SimulateRound(int round_number);
    Player DetermineWinner(const Player& left, const Player& right);
    void CollectLevelNodes(Node* node, int level,
                           std::vector<std::vector<Node*>>& levels);
};

#endif