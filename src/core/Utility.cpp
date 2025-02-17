#include "Utility.h"

#include <random>

int Utility::random(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(min, max);
    return dis(gen);
}

float Utility::random(const float min, const float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dis(min, max);
    return dis(gen);
}
