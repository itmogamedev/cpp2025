#include "Potion.h"
#include <sstream>
#include <iomanip>

Potion::Potion(const std::string& potionName, int potionPrice,
    double potionWeight, double potionDuration)
    : MagicItem(potionName, potionPrice, potionWeight), duration(potionDuration) {
}

std::string Potion::getSpecParam() const {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << duration;
    return stream.str();
}

double Potion::getDuration() const {
    return duration;
}