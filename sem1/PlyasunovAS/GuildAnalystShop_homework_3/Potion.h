#ifndef POTION_H
#define POTION_H

#include "MagicItem.h"

class Potion : public MagicItem {
private:
    double duration;

public:
    Potion(const std::string& potionName, int potionPrice,
        double potionWeight, double potionDuration);
    std::string getSpecParam() const override;
    double getDuration() const;
};

#endif