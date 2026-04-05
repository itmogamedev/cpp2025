#include "Shop.h"

#include <algorithm>
#include <iostream>
#include <map>

shop::shop(const std::string& shop_Name) : name(shop_Name) {}

void shop::addItem(std::unique_ptr<magicItem> item) {
  items.push_back(std::move(item));
}

void shop::analyzeShop() const {
  std::cout << "=== Магазин: " << name << " ===" << std::endl;
  std::cout << "Всего предметов: " << getItemCount() << std::endl;
  std::cout << "Средняя цена: " << getAveragePrice() << " золота" << std::endl;
  std::cout << "Средний вес: " << getAverageWeight() << " кг" << std::endl;
  std::cout << std::endl;

  std::cout << "Статистика по предметам:" << std::endl;
  printWeaponStats();
  printArmorStats();
  printPotionStats();
  printScrollStats();
  std::cout << std::endl;
}

std::string shop::getName() const { return name; }

int shop::getItemCount() const { return items.size(); }

double shop::getAveragePrice() const {
  if (items.empty()) return 0.0;
  double total = 0.0;
  for (const auto& item : items) {
    total += item->getPrice();
  }
  return total / items.size();
}

double shop::getAverageWeight() const {
  if (items.empty()) return 0.0;
  double total = 0.0;
  for (const auto& item : items) {
    total += item->getWeight();
  }
  return total / items.size();
}

void shop::printWeaponStats() const {
  int count = 0;
  double total_Damage = 0;

  for (const auto& item : items) {
    if (item->getType() == "Weapon") {
      total_Damage += item->getIntParam();
      count++;
    }
  }

  if (count > 0) {
    std::cout << "- Оружие: средний урон = " << (total_Damage / count)
              << std::endl;
  } else {
    std::cout << "- Оружие: нет в наличии" << std::endl;
  }
}

void shop::printArmorStats() const {
  int count = 0;
  double total_Defense = 0;

  for (const auto& item : items) {
    if (item->getType() == "Armor") {
      total_Defense += item->getIntParam();
      count++;
    }
  }

  if (count > 0) {
    std::cout << "- Броня: средняя защита = " << (total_Defense / count)
              << std::endl;
  } else {
    std::cout << "- Броня: нет в наличии" << std::endl;
  }
}

void shop::printPotionStats() const {
  int count = 0;
  double total_Duration = 0;

  for (const auto& item : items) {
    if (item->getType() == "Potion") {
      total_Duration += item->getDoubleParam();
      count++;
    }
  }

  if (count > 0) {
    std::cout << "- Зелья: средняя длительность = " << (total_Duration / count)
              << std::endl;
  } else {
    std::cout << "- Зелья: нет в наличии" << std::endl;
  }
}

void shop::printScrollStats() const {
  int count = 0;
  for (const auto& item : items) {
    if (item->getType() == "Scroll") {
      count++;
    }
  }

  if (count > 0) {
    std::string most_Frequent = getMostFrequentEffect();
    std::cout << "- Свитки: самый частый эффект " << most_Frequent << std::endl;
  } else {
    std::cout << "- Свитки: нет в наличии" << std::endl;
  }
}

std::string shop::getMostFrequentEffect() const {
  std::map<std::string, int> effect_Count;

  for (const auto& item : items) {
    if (item->getType() == "Scroll") {
      std::string effect = item->getStringParam();
      effect_Count[effect]++;
    }
  }

  if (effect_Count.empty()) {
    return "";
  }

  auto most_Frequent = std::max_element(
      effect_Count.begin(), effect_Count.end(),
      [](const auto& a, const auto& b) { return a.second < b.second; });

  return most_Frequent->first;
}
