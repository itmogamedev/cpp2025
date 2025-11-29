#ifndef SCROLL_H
#define SCROLL_H

#include "MagicItem.h"

class Scroll : public MagicItem {
private:
    std::string effect;

public:
    Scroll(const std::string& name, int price, double weight, const std::string& scrollEffect);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    std::string getEffect() const;
};

#endif