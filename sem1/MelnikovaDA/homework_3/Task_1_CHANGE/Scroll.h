#ifndef SCROLL_H
#define SCROLL_H

#include "MagicItem.h"

class scroll : public magicItem {
private:
    std::string effect;

public:
    scroll(const std::string& name, int price, double weight, const std::string& scroll_Effect);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    std::string getEffect() const;
};

#endif