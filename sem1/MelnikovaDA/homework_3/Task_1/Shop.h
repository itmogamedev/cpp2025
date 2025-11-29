#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include <memory>
#include "MagicItem.h"

class Shop {
private:
    std::string name;
    std::vector<std::unique_ptr<MagicItem>> items;

public:
    Shop(const std::string& shopName);

    void addItem(std::unique_ptr<MagicItem> item);
    void analyzeShop() const;

    std::string getName() const;
    int getItemCount() const;
    double getAveragePrice() const;
    double getAverageWeight() const;

private:
    void printWeaponStats() const;
    void printArmorStats() const;
    void printPotionStats() const;
    void printScrollStats() const;
    std::string getMostFrequentEffect() const;
};

#endif