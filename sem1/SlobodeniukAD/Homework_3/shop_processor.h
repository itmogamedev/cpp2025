//объ€вление класса ShopProcessor 
#pragma once
#include "item.h"
#include <memory>
#include <vector>
#include <string>

class ShopProcessor {
public:
    static void processFile(const std::string& filename);               

private:
    static void printShopReport(const std::string& shopName,
        const std::vector<std::unique_ptr<MagicItem>>& items);
    static double calculateAveragePrice(const std::vector<std::unique_ptr<MagicItem>>& items);
    static double calculateAverageWeight(const std::vector<std::unique_ptr<MagicItem>>& items);
};