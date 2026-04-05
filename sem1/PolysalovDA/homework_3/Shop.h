#ifndef SHOP_H
#define SHOP_H

#include "MagicItem.h"
#include <vector>
#include <string>

class Shop {
  private:
    std::string name;
    std::vector<MagicItem*> items;

  public:
    Shop(const std::string& n);
    ~Shop();

    void addItem(MagicItem* item);
    double getAveragePrice() const;
    double getAverageWeight() const;
    void printSpecParamStats() const;
    void printStats() const;
};

#endif