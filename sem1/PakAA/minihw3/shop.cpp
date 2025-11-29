#include "shop.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <variant>

#include "items.h"

// Устанавливаем кодировку консоли для корректного вывода русского текста
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

Shop::Shop(const std::string& shop_name) : name(shop_name) {
    static bool console_initialized = false;
    if (!console_initialized) {
        setUtf8Console();
        console_initialized = true;
    }
}

void Shop::addItem(std::unique_ptr<MagicItem> item) {
    items.push_back(std::move(item));
}

double Shop::calculateAveragePrice() const {
    if (items.empty()) return 0.0;
    double sum = std::accumulate(items.begin(), items.end(), 0.0,
        [](double total, const auto& item) {
            return total + item->price();
        });
    return sum / items.size();
}

double Shop::calculateAverageWeight() const {
    if (items.empty()) return 0.0;
    double sum = std::accumulate(items.begin(), items.end(), 0.0,
        [](double total, const auto& item) {
            return total + item->weight();
        });
    return sum / items.size();
}

void Shop::printItemStats() const {
    std::vector<const Weapon*> weapons;
    std::vector<const Armor*> armors;
    std::vector<const Potion*> potions;
    std::vector<const Scroll*> scrolls;

    for (const auto& item : items) {
        if (auto* w = dynamic_cast<Weapon*>(item.get())) {
            weapons.push_back(w);
        }
        else if (auto* a = dynamic_cast<Armor*>(item.get())) {
            armors.push_back(a);
        }
        else if (auto* p = dynamic_cast<Potion*>(item.get())) {
            potions.push_back(p);
        }
        else if (auto* s = dynamic_cast<Scroll*>(item.get())) {
            scrolls.push_back(s);
        }
    }

    std::cout << "\nСтатистика по предметам:\n";

    if (!weapons.empty()) {
        double avg = std::accumulate(weapons.begin(), weapons.end(), 0.0,
            [](double total, const Weapon* w) {
                return total + std::get<int>(w->getSpecParam());
            }) / weapons.size();
        std::cout << "- Оружие: средний урон = " << static_cast<int>(avg) << "\n";
    }
    else {
        std::cout << "- Оружие: нет в наличии\n";
    }

    if (!armors.empty()) {
        double avg = std::accumulate(armors.begin(), armors.end(), 0.0,
            [](double total, const Armor* a) {
                return total + std::get<int>(a->getSpecParam());
            }) / armors.size();
        std::cout << "- Броня: средняя защита = " << static_cast<int>(avg) << "\n";
    }
    else {
        std::cout << "- Броня: нет в наличии\n";
    }

    if (!potions.empty()) {
        double avg = std::accumulate(potions.begin(), potions.end(), 0.0,
            [](double total, const Potion* p) {
                return total + std::get<double>(p->getSpecParam());
            }) / potions.size();
        std::cout << "- Зелья: средняя длительность = "
            << std::fixed << std::setprecision(1) << avg << "\n";
    }
    else {
        std::cout << "- Зелья: нет в наличии\n";
    }

    if (!scrolls.empty()) {
        std::map<std::string, int> effect_count;
        for (const auto* s : scrolls) {
            effect_count[std::get<std::string>(s->getSpecParam())]++;
        }
        auto most_frequent = std::max_element(effect_count.begin(), effect_count.end(),
            [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
        std::cout << "- Свитки: самый частый эффект " << most_frequent->first << "\n";
    }
    else {
        std::cout << "- Свитки: нет в наличии\n";
    }
}

void Shop::printReport() const {
    std::cout << "=== Магазин: " << name << " ===\n";
    std::cout << "Всего предметов: " << items.size() << "\n";
    std::cout << "Средняя цена: " << std::fixed << std::setprecision(2)
        << calculateAveragePrice() << " золота\n";
    std::cout << "Средний вес: " << std::fixed << std::setprecision(2)
        << calculateAverageWeight() << " кг\n";
    printItemStats();
    std::cout << "\n";
}