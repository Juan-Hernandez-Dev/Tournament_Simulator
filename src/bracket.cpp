/// @file bracket.cpp
/// @author Juan
/// @brief Bracket implementation for tournament
/// @date 2025-11-04

#include "bracket.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "text_utils.h"

Bracket::Bracket() : root_(nullptr), total_levels_(0) {}

Bracket::~Bracket() {
    DestroyTree(root_);
}

void Bracket::DestroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
}

void Bracket::BuildFromQueue(PlayerQueue& queue) {
    BuildCompleteTree(queue);
    CollectByLevels();
}

void Bracket::BuildCompleteTree(PlayerQueue& queue) {
    int size = queue.Size();
    if (size == 0) {
        return;
    }

    /// Calculate tree height
    total_levels_ = static_cast<int>(std::ceil(std::log2(size)));
    int total_leaves = static_cast<int>(std::pow(2, total_levels_));

    /// Create all leaf nodes
    std::vector<Node*> leaves;
    for (int i = 0; i < total_leaves; i++) {
        if (!queue.IsEmpty()) {
            Player p = queue.Front();
            queue.Dequeue();
            leaves.push_back(new Node(p, total_levels_));
        } else {
            leaves.push_back(new Node(Player("BYE"), total_levels_));
        }
    }

    /// Build tree bottom-up
    std::vector<Node*> current_level = leaves;
    int level = total_levels_ - 1;

    while (current_level.size() > 1) {
        std::vector<Node*> next_level;

        for (size_t i = 0; i < current_level.size(); i += 2) {
            Node* parent = new Node(Player(), level);
            parent->left = current_level[i];
            parent->right = current_level[i + 1];
            next_level.push_back(parent);
        }

        current_level = next_level;
        level--;
    }

    root_ = current_level[0];
}

void Bracket::CollectByLevels() {
    if (root_ == nullptr) {
        return;
    }

    rounds_.clear();
    rounds_.resize(total_levels_ + 1);
    CollectLevelNodes(root_, 0, rounds_);
}

void Bracket::CollectLevelNodes(Node* node, int level,
                                 std::vector<std::vector<Node*>>& levels) {
    if (node == nullptr) {
        return;
    }

    levels[level].push_back(node);
    CollectLevelNodes(node->left, level + 1, levels);
    CollectLevelNodes(node->right, level + 1, levels);
}

void Bracket::Simulate() {
    if (root_ == nullptr) {
        return;
    }

    /// Simulate from leaves to root
    for (int round = total_levels_; round > 0; round--) {
        SimulateRound(round);
    }
}

void Bracket::SimulateRound(int round_number) {
    std::cout << "\n" << BOLD << "RONDA " << (total_levels_ - round_number + 1)
              << " " << RESET << std::endl;

    /// Simulate round time, with 3 seconds, without clearing the screen after
    MsgLoading("Ronda en curso", 3, false);

    for (Node* node : rounds_[round_number - 1]) {
        if (node->left == nullptr || node->right == nullptr) {
            continue;
        }

        Player left_player = node->left->value;
        Player right_player = node->right->value;

        Player winner = DetermineWinner(left_player, right_player);
        node->value = winner;

        std::cout << "(" << left_player.name << " vs "
                  << right_player.name << ") -> Gana: "
                  << winner.name << std::endl;
    }
}

Player Bracket::DetermineWinner(const Player& left, const Player& right) {
    /// If one is BYE, the other advances
    if (left.IsBye() && !right.IsBye()) {
        return right;
    }
    if (right.IsBye() && !left.IsBye()) {
        return left;
    }
    if (left.IsBye() && right.IsBye()) {
        return left;
    }

    /// Random winner (50/50)
    return (std::rand() % 2 == 0) ? left : right;
}

Player Bracket::Champion() const {
    if (root_ == nullptr) {
        return Player();
    }
    return root_->value;
}

void Bracket::PrintRounds() const {
    std::cout << "\n" << BOLD << "CAMPEÓN" << RESET << std::endl;
    std::cout << Champion().name << std::endl;
}