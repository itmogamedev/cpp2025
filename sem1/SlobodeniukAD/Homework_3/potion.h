//объ€вление класса potion
#pragma once
#include "item.h"

class Potion : public MagicItem {
public:
    Potion(std::string name, int price, double weight, double duration);
    void printSpecParam(std::ostream& os) const;
    const char* getTypeName() const;
    double getDuration() const { return duration; }

private:
    double duration;
};