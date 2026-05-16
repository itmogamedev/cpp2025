#include "shop_processor.h"
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

std::string findMode(const std::vector<std::string>& data) {
    if (data.empty()) return "";

    std::map<std::string, int> freq;
    for (const auto& str : data) {
        ++freq[str];
    }

    int maxCount = 0;
    std::string mode;
    for (const auto& pair : freq) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mode = pair.first;
        }
    }
    return mode;
}

void processShops(const std::vector<Shop>& shops, std::ostream& out) {
    for (const auto& shop : shops) {
        out << "=== Магазин: " << shop.name << " ===" << std::endl;
        out << "Всего предметов: " << shop.items.size() << std::endl;

        double totalPrice = 0.0;
        double totalWeight = 0.0;
        for (const auto& item : shop.items) {
            totalPrice += item->getPrice();
            totalWeight += item->getWeight();
        }

        double avgPrice = shop.items.empty() ? 0 : totalPrice / shop.items.size();
        double avgWeight = shop.items.empty() ? 0 : totalWeight / shop.items.size();

        out << std::fixed << std::setprecision(2);
        out << "Средняя цена: " << avgPrice << " золота" << std::endl;
        out << "Средний вес: " << avgWeight << " кг" << std::endl << std::endl;

        out << "Статистика по предметам:" << std::endl;

        std::vector<int> weaponParams;
        std::vector<int> armorParams;
        std::vector<double> potionParams;
        std::vector<std::string> scrollParams;

        for (const auto& item : shop.items) {
            auto param = item->getSpecParam();
            std::string type = item->getTypeName();

            if (type == "Weapon" && std::holds_alternative<int>(param)) {
                weaponParams.push_back(std::get<int>(param));
            }
            else if (type == "Armor" && std::holds_alternative<int>(param)) {
                armorParams.push_back(std::get<int>(param));
            }
            else if (type == "Potion" && std::holds_alternative<double>(param)) {
                potionParams.push_back(std::get<double>(param));
            }
            else if (type == "Scroll" && std::holds_alternative<std::string>(param)) {
                scrollParams.push_back(std::get<std::string>(param));
            }
        }

        if (!weaponParams.empty()) {
            double sum = 0.0;
            for (int d : weaponParams) sum += d;
            double avg = sum / weaponParams.size();
            out << "- Оружие: средний урон = " << std::fixed << std::setprecision(2) << avg << std::endl;
        }
        else {
            out << "- Оружие: нет в наличии" << std::endl;
        }

        if (!armorParams.empty()) {
            double sum = 0.0;
            for (int d : armorParams) sum += d;
            double avg = sum / armorParams.size();
            out << "- Броня: средняя защита = " << std::fixed << std::setprecision(2) << avg << std::endl;
        }
        else {
            out << "- Броня: нет в наличии" << std::endl;
        }

        if (!potionParams.empty()) {
            double sum = 0.0;
            for (double d : potionParams) sum += d;
            double avg = sum / potionParams.size();
            out << "- Зелья: средняя длительность = " << std::fixed << std::setprecision(2) << avg << std::endl;
        }
        else {
            out << "- Зелья: нет в наличии" << std::endl;
        }

        if (!scrollParams.empty()) {
            std::string mode = findMode(scrollParams);
            out << "- Свитки: самый частый эффект " << mode << std::endl;
        }
        else {
            out << "- Свитки: нет в наличии" << std::endl;
        }

        out << std::endl;
    }
}