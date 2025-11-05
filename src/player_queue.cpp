/// @file player_queue.cpp
/// @author Juan
/// @brief Circular queue implementation
/// @date 2025-11-04

#include "player_queue.h"
#include <iostream>

PlayerQueue::PlayerQueue(int capacity)
    : capacity_(capacity), front_(0), rear_(-1), size_(0) {
    queue_ = new Player[capacity_];
}

PlayerQueue::~PlayerQueue() {
    delete[] queue_;
}

bool PlayerQueue::Enqueue(const Player& player) {
    if (IsFull()) {
        return false;
    }

    rear_ = (rear_ + 1) % capacity_;
    queue_[rear_] = player;
    size_++;
    return true;
}

bool PlayerQueue::Dequeue() {
    if (IsEmpty()) {
        return false;
    }

    front_ = (front_ + 1) % capacity_;
    size_--;
    return true;
}

bool PlayerQueue::IsEmpty() const {
    return size_ == 0;
}

bool PlayerQueue::IsFull() const {
    return size_ == capacity_;
}

Player PlayerQueue::Front() const {
    if (IsEmpty()) {
        return Player();
    }
    return queue_[front_];
}

void PlayerQueue::Print() const {
    if (IsEmpty()) {
        std::cout << "[Empty queue]" << std::endl;
        return;
    }

    std::cout << "[front ->] ";
    int index = front_;
    for (int i = 0; i < size_; i++) {
        std::cout << queue_[index].name;
        if (i < size_ - 1) {
            std::cout << ", ";
        }
        index = (index + 1) % capacity_;
    }
    std::cout << std::endl;
}

int PlayerQueue::Size() const {
    return size_;
}