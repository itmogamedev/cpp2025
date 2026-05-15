// MiniHomeWork3.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "MagicItem.h"

struct Shop {
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};

void printShopStats(const Shop& shop) {
  std::cout << "=== Магазин: " << shop.name << " ===\n";

  std::size_t totalItems = shop.items.size();
  std::cout << "Всего предметов: " << totalItems << "\n";

  double sumPrice = 0.0;
  double sumWeight = 0.0;

  long long weaponSum = 0;
  int weaponCount = 0;

  long long armorSum = 0;
  int armorCount = 0;

  double potionSum = 0.0;
  int potionCount = 0;

  std::unordered_map<std::string, int> scrollFreq;
  int scrollCount = 0;

  for (const auto& itemPtr : shop.items) {
    sumPrice += itemPtr->getPrice();
    sumWeight += itemPtr->getWeight();

    std::string type = itemPtr->getTypeName();
    auto spec = itemPtr->getSpecParam();

    if (type == "Оружие") {
      int dmg = std::get<int>(spec);
      weaponSum += dmg;
      weaponCount++;
    } else if (type == "Броня") {
      int def = std::get<int>(spec);
      armorSum += def;
      armorCount++;
    } else if (type == "Зелье") {
      double dur = std::get<double>(spec);
      potionSum += dur;
      potionCount++;
    } else if (type == "Свиток") {
      std::string eff = std::get<std::string>(spec);
      scrollFreq[eff]++;
      scrollCount++;
    }
  }

  std::cout << std::fixed << std::setprecision(2);

  if (totalItems > 0) {
    double avgPrice = sumPrice / static_cast<double>(totalItems);
    double avgWeight = sumWeight / static_cast<double>(totalItems);
    std::cout << "Средняя цена: " << avgPrice << " золота\n";
    std::cout << "Средний вес: " << avgWeight << " кг\n";
  } else {
    std::cout << "Средняя цена: 0.00 золота\n";
    std::cout << "Средний вес: 0.00 кг\n";
  }

  std::cout << "\nСтатистика по предметам:\n";

  std::cout << "- Оружие: ";
  if (weaponCount > 0) {
    double avgDamage = static_cast<double>(weaponSum) / weaponCount;
    std::cout << "средний урон = " << avgDamage << "\n";
  } else {
    std::cout << "нет в наличии\n";
  }

  std::cout << "- Броня: ";
  if (armorCount > 0) {
    double avgDefense = static_cast<double>(armorSum) / armorCount;
    std::cout << "средняя защита = " << avgDefense << "\n";
  } else {
    std::cout << "нет в наличии\n";
  }

  std::cout << "- Зелья: ";
  if (potionCount > 0) {
    double avgDuration = potionSum / potionCount;
    std::cout << "средняя длительность = " << avgDuration << "\n";
  } else {
    std::cout << "нет в наличии\n";
  }

  std::cout << "- Свитки: ";
  if (scrollCount > 0) {
    std::string bestEffect;
    int bestCount = 0;
    for (const auto& pair : scrollFreq) {
      if (pair.second > bestCount) {
        bestCount = pair.second;
        bestEffect = pair.first;
      }
    }
    std::cout << "самый частый эффект " << bestEffect << "\n";
  } else {
    std::cout << "нет в наличии\n";
  }

  std::cout << "\n";
}

int main() {
  std::setlocale(LC_ALL, "Russian");
  std::ifstream inShops("shops.txt");
  if (!inShops.is_open()) {
    std::cerr << "Can't open shops.txt\n";
    return 1;
  }

  std::vector<Shop> shops;
  std::string token;

  while (inShops >> token) {
    if (token != "Магазин:") {
      continue;
    }

    Shop shop;
    if (!(inShops >> shop.name)) {
      break;
    }

    std::string itemsLabel;
    int itemsCount = 0;
    if (!(inShops >> itemsLabel >> itemsCount)) {
      break;
    }

    for (int i = 0; i < itemsCount; ++i) {
      std::string type;
      std::string itemName;
      int price;
      double weight;

      if (!(inShops >> type >> itemName >> price >> weight)) {
        break;
      }

      if (type == "Оружие") {
        int damage;
        inShops >> damage;
        shop.items.push_back(
            std::make_unique<Weapon>(itemName, price, weight, damage));
      } else if (type == "Броня") {
        int defense;
        inShops >> defense;
        shop.items.push_back(
            std::make_unique<Armor>(itemName, price, weight, defense));
      } else if (type == "Зелье") {
        double duration;
        inShops >> duration;
        shop.items.push_back(
            std::make_unique<Potion>(itemName, price, weight, duration));
      } else if (type == "Свиток") {
        std::string effect;
        inShops >> effect;
        shop.items.push_back(
            std::make_unique<Scroll>(itemName, price, weight, effect));
      }
    }

    shops.push_back(std::move(shop));
  }

  for (const auto& shop : shops) {
    printShopStats(shop);
  }

  return 0;
}
