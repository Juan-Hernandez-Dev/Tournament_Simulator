/// @file luck_checker.h
/// @author Juan
/// @brief The sacred luck dog validator
/// @date 2025-11-04

#ifndef LUCK_CHECKER_H
#define LUCK_CHECKER_H

#include <string>

/// Check if the luck dog is still protecting us
/// Returns true if everything is fine, false if doom is upon us
bool ValidateLuckDog();

/// Display the curse message when luck dog is disturbed
void ShowCurseMessage();

#endif