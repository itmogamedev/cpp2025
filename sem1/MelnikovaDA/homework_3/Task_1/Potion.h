#ifndef POTION_H
#define POTION_H

#include "MagicItem.h"

class Potion : public MagicItem {
private:
    double duration;

public:
    Potion(const std::string& name, int price, double weight, double potionDuration);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    double getDuration() const;
};

#endif