#ifndef POTION_H
#define POTION_H

#include "MagicItem.h"

class potion : public magicItem {
private:
    double duration;

public:
    potion(const std::string& name, int price, double weight, double potion_Duration);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    double getDuration() const;
};

#endif