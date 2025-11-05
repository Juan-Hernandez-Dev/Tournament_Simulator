/// @file player_queue.h
/// @author Juan
/// @brief Circular queue implementation for players
/// @date 2025-11-04

#ifndef PLAYER_QUEUE_H
#define PLAYER_QUEUE_H

#include "player.h"

class PlayerQueue {
  public:
    PlayerQueue(int capacity);
    ~PlayerQueue();

    bool Enqueue(const Player& player);
    bool Dequeue();
    bool IsEmpty() const;
    bool IsFull() const;
    Player Front() const;
    void Print() const;
    int Size() const;

  private:
    Player* queue_;
    int capacity_;
    int front_;
    int rear_;
    int size_;
};

#endif