#include "Shop.h"
#include <algorithm>
#include <iostream>
#include <map>

Shop::Shop(const std::string& shopName) : name(shopName) {}

void Shop::addItem(std::unique_ptr<MagicItem> item) {
  items.push_back(std::move(item));
}

void Shop::analyzeShop() const {
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

std::string Shop::getName() const { return name; }

int Shop::getItemCount() const { return items.size(); }

double Shop::getAveragePrice() const {
  if (items.empty()) return 0.0;
  double total = 0.0;
  for (const auto& item : items) {
    total += item->getPrice();
  }
  return total / items.size();
}

double Shop::getAverageWeight() const {
  if (items.empty()) return 0.0;
  double total = 0.0;
  for (const auto& item : items) {
    total += item->getWeight();
  }
  return total / items.size();
}

void Shop::printWeaponStats() const {
  int count = 0;
  double totalDamage = 0;

  for (const auto& item : items) {
    if (item->getType() == "Weapon") {
      totalDamage += item->getIntParam();
      count++;
    }
  }

  if (count > 0) {
    std::cout << "- Оружие: средний урон = " << (totalDamage / count)
              << std::endl;
  } else {
    std::cout << "- Оружие: нет в наличии" << std::endl;
  }
}

void Shop::printArmorStats() const {
  int count = 0;
  double totalDefense = 0;

  for (const auto& item : items) {
    if (item->getType() == "Armor") {
      totalDefense += item->getIntParam();
      count++;
    }
  }

  if (count > 0) {
    std::cout << "- Броня: средняя защита = " << (totalDefense / count)
              << std::endl;
  } else {
    std::cout << "- Броня: нет в наличии" << std::endl;
  }
}

void Shop::printPotionStats() const {
  int count = 0;
  double totalDuration = 0;

  for (const auto& item : items) {
    if (item->getType() == "Potion") {
      totalDuration += item->getDoubleParam();
      count++;
    }
  }

  if (count > 0) {
    std::cout << "- Зелья: средняя длительность = " << (totalDuration / count)
              << std::endl;
  } else {
    std::cout << "- Зелья: нет в наличии" << std::endl;
  }
}

void Shop::printScrollStats() const {
  int count = 0;
  for (const auto& item : items) {
    if (item->getType() == "Scroll") {
      count++;
    }
  }

  if (count > 0) {
    std::string mostFrequent = getMostFrequentEffect();
    std::cout << "- Свитки: самый частый эффект " << mostFrequent << std::endl;
  } else {
    std::cout << "- Свитки: нет в наличии" << std::endl;
  }
}

std::string Shop::getMostFrequentEffect() const {
  std::map<std::string, int> effectCount;

  for (const auto& item : items) {
    if (item->getType() == "Scroll") {
      std::string effect = item->getStringParam();
      effectCount[effect]++;
    }
  }

  if (effectCount.empty()) {
    return "";
  }

  auto mostFrequent = std::max_element(
      effectCount.begin(), effectCount.end(),
      [](const auto& a, const auto& b) { return a.second < b.second; });

  return mostFrequent->first;
}
