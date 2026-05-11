#ifndef SCROLL_H
#define SCROLL_H

#include "MagicItem.h"

class Scroll : public MagicItem {
private:
    std::string effect;

public:
    Scroll(const std::string& scrollName, int scrollPrice,
        double scrollWeight, const std::string& scrollEffect);
    std::string getSpecParam() const override;
    std::string getEffect() const;
};

#endif