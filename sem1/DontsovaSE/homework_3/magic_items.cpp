#include "magic_items.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <iomanip>

// MagicItem
MagicItem::MagicItem(const std::string& name, double price, double weight)
    : name(name), price(price), weight(weight) {}

std::string MagicItem::getName() const { return name; }
double MagicItem::getPrice() const { return price; }
double MagicItem::getWeight() const { return weight; }

// Weapon
Weapon::Weapon(const std::string& name, double price, double weight, int damage)
    : MagicItem(name, price, weight), damage(damage) {}

std::string Weapon::getType() const { return "Оружие"; }
SpecificParam Weapon::getSpecificParam() const { return damage; }
int Weapon::getDamage() const { return damage; }

// Armor
Armor::Armor(const std::string& name, double price, double weight, int defense)
    : MagicItem(name, price, weight), defense(defense) {}

std::string Armor::getType() const { return "Броня"; }
SpecificParam Armor::getSpecificParam() const { return defense; }
int Armor::getDefense() const { return defense; }

// Potion
Potion::Potion(const std::string& name, double price, double weight, 
               double duration)
    : MagicItem(name, price, weight), duration(duration) {}

std::string Potion::getType() const { return "Зелье"; }
SpecificParam Potion::getSpecificParam() const { return duration; }
double Potion::getDuration() const { return duration; }

// Scroll
Scroll::Scroll(const std::string& name, double price, double weight,
               const std::string& effect)
    : MagicItem(name, price, weight), effect(effect) {}

std::string Scroll::getType() const { return "Свиток"; }
SpecificParam Scroll::getSpecificParam() const { return effect; }
std::string Scroll::getEffect() const { return effect; }

// Shop
Shop::Shop(const std::string& name) : shop_name(name) {}

Shop::~Shop() {
    for (auto item : items) {
        delete item;
    }
}

void Shop::addItem(MagicItem* item) {
    items.push_back(item);
}

std::string Shop::getName() const { return shop_name; }
const std::vector<MagicItem*>& Shop::getItems() const { return items; }

double Shop::calculateAveragePrice() const {
    if (items.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& item : items) {
        sum += item->getPrice();
    }
    return sum / items.size();
}

double Shop::calculateAverageWeight() const {
    if (items.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& item : items) {
        sum += item->getWeight();
    }
    return sum / items.size();
}

void Shop::analyzeSpecificParams() const {
    std::map<std::string, std::vector<SpecificParam>> params_by_type;
    
    for (const auto& item : items) {
        std::string type = item->getType();
        SpecificParam param = item->getSpecificParam();
        params_by_type[type].push_back(param);
    }
    
    std::vector<std::string> all_types = {"Оружие", "Броня", "Зелье", "Свиток"};
    
    for (const auto& type : all_types) {
        std::cout << "- " << type << ": ";
        
        if (params_by_type.find(type) == params_by_type.end()) {
            std::cout << "нет в наличии" << std::endl;
            continue;
        }
        
        const auto& params = params_by_type[type];
        
        if (type == "Оружие") {
            int sum = 0;
            for (const auto& param : params) {
                sum += std::get<int>(param);
            }
            double average = static_cast<double>(sum) / params.size();
            std::cout << "средний урон = " << std::fixed 
                      << std::setprecision(0) << average << std::endl;
        } else if (type == "Броня") {
            int sum = 0;
            for (const auto& param : params) {
                sum += std::get<int>(param);
            }
            double average = static_cast<double>(sum) / params.size();
            std::cout << "средняя защита = " << std::fixed 
                      << std::setprecision(0) << average << std::endl;
        } else if (type == "Зелье") {
            double sum = 0.0;
            for (const auto& param : params) {
                sum += std::get<double>(param);
            }
            double average = sum / params.size();
            std::cout << "средняя длительность = " << std::fixed 
                      << std::setprecision(1) << average << std::endl;
        } else if (type == "Свиток") {
            std::map<std::string, int> frequency;
            for (const auto& param : params) {
                std::string value = std::get<std::string>(param);
                frequency[value]++;
            }
            
            auto max_elem = std::max_element(
                frequency.begin(), frequency.end(),
                [](const auto& a, const auto& b) {
                    return a.second < b.second;
                });
            
            std::cout << "самый частый эффект " << max_elem->first << std::endl;
        }
    }
}
