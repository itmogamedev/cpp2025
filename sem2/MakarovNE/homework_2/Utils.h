#pragma once
#include <chrono>
#include <random>

namespace Utils {

static std::mt19937 randomEngine(static_cast<unsigned int>(
    std::chrono::system_clock::now().time_since_epoch().count()));

int randomInt(int min, int max);
float randomFloat(float min, float max);

}  // namespace Utils
