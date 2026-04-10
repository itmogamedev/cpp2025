#include "Shop.h"

#include <iostream>

#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

Shop::Shop(const std::string& shopName) { name = shopName; }

void Shop::introduceSelf() const {
  std::cout << "=== Shop: " << name << " ===" << std::endl;
  std::cout << "Items count: " << items.size() << std::endl;
  std::cout << "Average price: " << calculateAveragePrice() << " coins"
            << std::endl;
  std::cout << "Average weight: " << calculateAverageWeight() << " kg"
            << std::endl;
  std::cout << std::endl;
}

double Shop::calculateAveragePrice() const {
  double average = 0.0;
  for (const auto& item : items) {
    average += item->getPrice();
  }
  return (average / items.size());
}

double Shop::calculateAverageWeight() const {
  double average = 0.0;
  for (const auto& item : items) {
    average += item->getWeight();
  }
  return (average / items.size());
}

void Shop::showItems() const {
  std::cout << "=== Shop: " << name << " ===" << std::endl;
  for (const auto& item : items) {
    item->introduceSelf();
  }
}

void Shop::addItem(std::unique_ptr<MagicItem> elem) {
  items.push_back(std::move(elem));
}

void Shop::calculateStatistics() const {
  double totalDamage = 0.0;
  int totalWeaponsCount = 0;
  double totalDefence = 0.0;
  int totalArmorsCount = 0;
  double totalDuration = 0.0;
  int totalPotionsCount = 0;
  size_t itemsCount = items.size();
  std::map<std::string, int> totalSpells;

  for (const auto& item : items) {
    if (auto* weapon = dynamic_cast<Weapon*>(item.get())) {
      totalDamage += std::get<int>(weapon->getSpecParam());
      ++totalWeaponsCount;
    } else if (auto* armor = dynamic_cast<Armor*>(item.get())) {
      totalDefence += std::get<int>(armor->getSpecParam());
      ++totalArmorsCount;
    } else if (auto* potion = dynamic_cast<Potion*>(item.get())) {
      totalDuration += std::get<double>(potion->getSpecParam());
      ++totalPotionsCount;
    } else if (auto* scroll = dynamic_cast<Scroll*>(item.get())) {
      std::string scrollName = std::get<std::string>(scroll->getSpecParam());
      totalSpells[scrollName]++;
    }
  }

  auto mostOftenSpell =
      std::max_element(totalSpells.cbegin(), totalSpells.cend(),
                       [](const auto& lhs, const auto& rhs) -> bool {
                         return (lhs.second < rhs.second);
                       });

  std::string spellStatistic = mostOftenSpell == totalSpells.cend()
                                   ? "out of stock"
                                   : mostOftenSpell->first;
  if (totalWeaponsCount > 0) {
    std::cout << "Weapon: average damage = "
              << (totalDamage / totalWeaponsCount) << std::endl;
  } else {
    std::cout << "Weapon: out of stock" << std::endl;
  }
  if (totalArmorsCount > 0) {
    std::cout << "Armor: average defence = "
              << (totalDefence / totalArmorsCount) << std::endl;
  } else {
    std::cout << "Armor: out of stock" << std::endl;
  }
  if (totalPotionsCount > 0) {
    std::cout << "Potion: average duration = "
              << (totalDuration / totalPotionsCount) << std::endl;
  } else {
    std::cout << "Potion: out of stock " << std::endl;
  }
  std::cout << "Scroll: most often = " << spellStatistic << std::endl;
}
