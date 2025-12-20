#include "shop.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "items.h"

#ifdef _WIN32
#include <windows.h>
void setUtf8Console() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}
#else
void setUtf8Console() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
}
#endif

Shop::Shop(const std::string& shop_name) : name_(shop_name) {
    static bool console_initialized = false;
    if (!console_initialized) {
        setUtf8Console();
        console_initialized = true;
    }
}

void Shop::addItem(std::unique_ptr<MagicItem> item) {
    items_.push_back(std::move(item));
}

double Shop::calculateAveragePrice() const {
    if (items_.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& item : items_) {
        sum += item->getPrice();
    }
    return sum / items_.size();
}

double Shop::calculateAverageWeight() const {
    if (items_.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& item : items_) {
        sum += item->getWeight();
    }
    return sum / items_.size();
}

void Shop::printItemStats() const {
    std::vector<const Weapon*> weapons;
    std::vector<const Armor*> armors;
    std::vector<const Potion*> potions;
    std::vector<const Scroll*> scrolls;

    for (const auto& item : items_) {
        if (auto* w = dynamic_cast<const Weapon*>(item.get())) {
            weapons.push_back(w);
        }
        else if (auto* a = dynamic_cast<const Armor*>(item.get())) {
            armors.push_back(a);
        }
        else if (auto* p = dynamic_cast<const Potion*>(item.get())) {
            potions.push_back(p);
        }
        else if (auto* s = dynamic_cast<const Scroll*>(item.get())) {
            scrolls.push_back(s);
        }
    }

    std::cout << "\nСтатистика по предметам:\n";

    if (!weapons.empty()) {
        double total_damage = 0.0;
        for (const auto* w : weapons) {
            total_damage += std::stoi(w->getSpecialParam());
        }
        double avg_damage = total_damage / weapons.size();
        std::cout << "- Оружие: средний урон = " << static_cast<int>(avg_damage)
            << "\n";
    }
    else {
        std::cout << "- Оружие: нет в наличии\n";
    }

    if (!armors.empty()) {
        double total_defense = 0.0;
        for (const auto* a : armors) {
            total_defense += std::stoi(a->getSpecialParam());
        }
        double avg_defense = total_defense / armors.size();
        std::cout << "- Броня: средняя защита = " << static_cast<int>(avg_defense)
            << "\n";
    }
    else {
        std::cout << "- Броня: нет в наличии\n";
    }

    if (!potions.empty()) {
        double total_duration = 0.0;
        for (const auto* p : potions) {
            total_duration += std::stod(p->getSpecialParam());
        }
        double avg_duration = total_duration / potions.size();
        std::cout << "- Зелья: средняя длительность = " << std::fixed
            << std::setprecision(1) << avg_duration << "\n";
    }
    else {
        std::cout << "- Зелья: нет в наличии\n";
    }

    if (!scrolls.empty()) {
        std::map<std::string, int> effect_count;
        for (const auto* s : scrolls) {
            effect_count[s->getSpecialParam()]++;
        }

        std::string most_common_effect;
        int max_count = 0;
        for (const auto& pair : effect_count) {
            if (pair.second > max_count) {
                max_count = pair.second;
                most_common_effect = pair.first;
            }
        }
        std::cout << "- Свитки: самый частый эффект " << most_common_effect << "\n";
    }
    else {
        std::cout << "- Свитки: нет в наличии\n";
    }
}

void Shop::printReport() const {
    std::cout << "=== Магазин: " << name_ << " ===\n";
    std::cout << "Всего предметов: " << items_.size() << "\n";
    std::cout << "Средняя цена: " << std::fixed << std::setprecision(2)
        << calculateAveragePrice() << " золота\n";
    std::cout << "Средний вес: " << std::fixed << std::setprecision(2)
        << calculateAverageWeight() << " кг\n";
    printItemStats();
    std::cout << "\n";
}