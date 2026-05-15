#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>
#include <iomanip>
#include <Windows.h>

#include "MagicItem.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"

struct Shop {
    std::string name;
    std::vector<std::unique_ptr<MagicItem>> items;
};

std::vector<Shop> readShopsFromFile(const std::string& filename) {
    std::vector<Shop> shops;
    std::ifstream file(filename);
    std::string line;

    Shop currentShop;
    bool readingItems = false;
    int itemsToRead = 0;
    int itemsRead = 0;

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return shops;
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.find("Магазин: ") == 0) {
            if (!currentShop.name.empty()) {
                shops.push_back(std::move(currentShop));
            }
            currentShop = Shop();
            currentShop.name = line.substr(9);
            readingItems = false;
        }
        else if (line.find("Предметы: ") == 0) {
            itemsToRead = std::stoi(line.substr(10));
            readingItems = true;
            itemsRead = 0;
        }
        else if (readingItems && itemsRead < itemsToRead) {
            std::istringstream iss(line);
            std::string type, name;
            int price;
            double weight;

            iss >> type >> name >> price >> weight;

            if (type == "Оружие") {
                int damage;
                iss >> damage;
                currentShop.items.push_back(
                    std::make_unique<Weapon>(name, price, weight, damage)
                );
            }
            else if (type == "Броня") {
                int defense;
                iss >> defense;
                currentShop.items.push_back(
                    std::make_unique<Armor>(name, price, weight, defense)
                );
            }
            else if (type == "Зелье") {
                double duration;
                iss >> duration;
                currentShop.items.push_back(
                    std::make_unique<Potion>(name, price, weight, duration)
                );
            }
            else if (type == "Свиток") {
                std::string effect;
                iss >> effect;
                currentShop.items.push_back(
                    std::make_unique<Scroll>(name, price, weight, effect)
                );
            }

            itemsRead++;
        }
    }

    if (!currentShop.name.empty()) {
        shops.push_back(std::move(currentShop));
    }

    return shops;
}

void analyzeShops(const std::vector<Shop>& shops) {
    for (const auto& shop : shops) {
        std::cout << "Магазин: " << shop.name << " ===\n";
        std::cout << "Всего предметов: " << shop.items.size() << "\n";

        double totalPrice = 0;
        double totalWeight = 0;

        std::vector<int> weaponDamages;
        std::vector<int> armorDefenses;
        std::vector<double> potionDurations;
        std::vector<std::string> scrollEffects;

        for (const auto& item : shop.items) {
            totalPrice += item->getPrice();
            totalWeight += item->getWeight();

            if (auto weapon = dynamic_cast<const Weapon*>(item.get())) {
                weaponDamages.push_back(weapon->getDamage());
            }
            else if (auto armor = dynamic_cast<const Armor*>(item.get())) {
                armorDefenses.push_back(armor->getDefense());
            }
            else if (auto potion = dynamic_cast<const Potion*>(item.get())) {
                potionDurations.push_back(potion->getDuration());
            }
            else if (auto scroll = dynamic_cast<const Scroll*>(item.get())) {
                scrollEffects.push_back(scroll->getEffect());
            }
        }

        double avgPrice = totalPrice / shop.items.size();
        double avgWeight = totalWeight / shop.items.size();

        std::cout << "Средняя цена: " << avgPrice << " золота\n";
        std::cout << "Средний вес: " << avgWeight << " кг\n\n";

        std::cout << "Статистика по предметам:\n";

        if (!weaponDamages.empty()) {
            double avgDamage = 0;
            for (int damage : weaponDamages) avgDamage += damage;
            avgDamage /= weaponDamages.size();
            std::cout << "- Оружие: средний урон = " << avgDamage << "\n";
        }
        else {
            std::cout << "- Оружие: нет в наличии\n";
        }

        if (!armorDefenses.empty()) {
            double avgDefense = 0;
            for (int defense : armorDefenses) avgDefense += defense;
            avgDefense /= armorDefenses.size();
            std::cout << "- Броня: средняя защита = " << avgDefense << "\n";
        }
        else {
            std::cout << "- Броня: нет в наличии\n";
        }

        if (!potionDurations.empty()) {
            double avgDuration = 0;
            for (double duration : potionDurations) avgDuration += duration;
            avgDuration /= potionDurations.size();
            std::cout << "- Зелья: средняя длительность = " << avgDuration << "\n";
        }
        else {
            std::cout << "- Зелья: нет в наличии\n";
        }

        if (!scrollEffects.empty()) {
            std::map<std::string, int> effectCount;
            for (const auto& effect : scrollEffects) {
                effectCount[effect]++;
            }

            std::string mostCommonEffect;
            int maxCount = 0;
            for (const auto& pair : effectCount) {
                if (pair.second > maxCount) {
                    mostCommonEffect = pair.first;
                    maxCount = pair.second;
                }
            }

            std::cout << "- Свитки: самый частый эффект " << mostCommonEffect << "\n";
        }
        else {
            std::cout << "- Свитки: нет в наличии\n";
        }

        std::cout << "\n" << std::string(40, '-') << "\n\n";
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try {
        auto shops = readShopsFromFile("magic_shops.txt");
        if (shops.empty()) {
            std::cerr << "Не удалось загрузить данные магазинов. Проверьте файл magic_shops.txt" << std::endl;
            return 1;
        }
        analyzeShops(shops);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Нажмите Enter для выхода...";
    std::cin.get();

    return 0;
}