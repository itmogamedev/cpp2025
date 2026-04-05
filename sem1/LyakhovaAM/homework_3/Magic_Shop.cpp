#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include "MagicItem.h"

std::map<std::string, std::vector<std::unique_ptr<MagicItem>>> catalog;
void readFile(std::ifstream& file);
void calculateStatistics(std::string name_of_shop);

int main() {
  std::ifstream file;
  file.open("shops.txt");
  readFile(file);
  for (auto& shop : catalog) calculateStatistics(shop.first);
  file.close();
  return 0;
}

void readFile(std::ifstream& file) {
  std::string name_of_shop;
  while (file >> name_of_shop) {
    int number_of_items;
    file >> number_of_items;
    while (number_of_items--) {
      std::string type, name;
      int price;
      double weight;
      file >> type;
      if (type == "Scroll") {
        std::string special_param;
        file >> name >> price >> weight >> special_param;
        catalog[name_of_shop].emplace_back(
            std::make_unique<Scroll>(name, price, weight, special_param));
      } else if (type == "Potion") {
        double special_param;
        file >> name >> price >> weight >> special_param;
        catalog[name_of_shop].emplace_back(
            std::make_unique<Potion>(name, price, weight, special_param));
      } else {
        int special_param;
        file >> name >> price >> weight >> special_param;
        if (type == "Weapon")
          catalog[name_of_shop].emplace_back(
              std::make_unique<Weapon>(name, price, weight, special_param));
        else
          catalog[name_of_shop].emplace_back(
              std::make_unique<Armor>(name, price, weight, special_param));
      }
    }
  }
}

void calculateStatistics(std::string name_of_shop) {
  double weight = 0, damage = 0, defense = 0, duration = 0;
  int price = 0;
  int number_of_weapons = 0, number_of_armors = 0, number_of_potions = 0,
      max_effects = 0;
  std::map<std::string, int> effects;
  for (auto& item : catalog[name_of_shop]) {
    price += item->getPrice();
    weight += item->getWeight();
    if (item->getType() == "Weapon") {
      ++number_of_weapons;
      damage += get<int>(item->getSpecParam());
    }
    if (item->getType() == "Armor") {
      ++number_of_armors;
      defense += get<int>(item->getSpecParam());
    }
    if (item->getType() == "Potion") {
      ++number_of_potions;
      duration += get<double>(item->getSpecParam());
    }
    if (item->getType() == "Scroll") {
      ++effects[get<std::string>(item->getSpecParam())];
      max_effects = std::max(max_effects,
                             effects[get<std::string>(item->getSpecParam())]);
    }
  }
  std::cout << "=== Shop: " << name_of_shop << " ===\n"
            << "Total items: " << catalog[name_of_shop].size() << '\n'
            << "Average price: " << price << " gold\n"
            << "Item statistics:\n"
            << "- Weapons: ";
  if (number_of_weapons)
    std::cout << "average damage = " << damage / number_of_weapons << '\n';
  else
    std::cout << "not available\n";
  std::cout << "- Armors: ";
  if (number_of_armors)
    std::cout << "average defense = " << defense / number_of_armors << '\n';
  else
    std::cout << "not available\n";
  std::cout << "- Potions: ";
  if (number_of_potions)
    std::cout << "average duration = " << duration / number_of_potions << '\n';
  else
    std::cout << "not available\n";
  std::cout << "- Scrolls:";
  if (effects.size()) {
    for (auto& effect : effects)
      if (effect.second == max_effects) std::cout << ' ' << effect.first;
    std::cout << '\n';
  } else
    std::cout << " not available\n";
  std::cout << '\n';
}
