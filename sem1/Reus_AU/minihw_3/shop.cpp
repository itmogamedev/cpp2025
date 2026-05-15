#include "shop.h"

#include <iomanip>
#include <iostream>
#include <map>

Shop::Shop(const std::string& n) : name(n) {}

void Shop::addItem(std::shared_ptr<MagicItem> item) { items.push_back(item); }

void Shop::analyze() const {
  std::cout << "\n=== Shop: " << name << " ===" << std::endl;
  std::cout << "Total items: " << items.size() << std::endl;

  // Average price
  double avg_price = 0;
  for (const auto& item : items) {
    avg_price += item->getPrice();
  }
  avg_price /= items.size();
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Average price: " << avg_price << " gold" << std::endl;

  // Average weight
  double avg_weight = 0;
  for (const auto& item : items) {
    avg_weight += item->getWeight();
  }
  avg_weight /= items.size();
  std::cout << "Average weight: " << avg_weight << " kg" << std::endl;

  // Statistics by type
  std::cout << "\nItem statistics:" << std::endl;
  analyzeWeapons();
  analyzeArmor();
  analyzePotions();
  analyzeScrolls();
}

void Shop::analyzeWeapons() const {
  std::vector<int> damages;
  for (const auto& item : items) {
    if (item->getType() == "Weapon") {
      damages.push_back(std::get<int>(item->getSpecParam()));
    }
  }

  if (damages.empty()) {
    std::cout << "- Weapons: not available" << std::endl;
  } else {
    double avg = 0;
    for (int d : damages) {
      avg += d;
    }
    avg /= damages.size();
    std::cout << "- Weapons: average damage = " << static_cast<int>(avg)
              << std::endl;
  }
}

void Shop::analyzeArmor() const {
  std::vector<int> defenses;
  for (const auto& item : items) {
    if (item->getType() == "Armor") {
      defenses.push_back(std::get<int>(item->getSpecParam()));
    }
  }

  if (defenses.empty()) {
    std::cout << "- Armor: not available" << std::endl;
  } else {
    double avg = 0;
    for (int d : defenses) {
      avg += d;
    }
    avg /= defenses.size();
    std::cout << "- Armor: average defense = " << static_cast<int>(avg)
              << std::endl;
  }
}

void Shop::analyzePotions() const {
  std::vector<double> durations;
  for (const auto& item : items) {
    if (item->getType() == "Potion") {
      durations.push_back(std::get<double>(item->getSpecParam()));
    }
  }

  if (durations.empty()) {
    std::cout << "- Potions: not available" << std::endl;
  } else {
    double avg = 0;
    for (double d : durations) {
      avg += d;
    }
    avg /= durations.size();
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "- Potions: average duration = " << avg << std::endl;
  }
}

void Shop::analyzeScrolls() const {
  std::map<std::string, int> effect_count;
  for (const auto& item : items) {
    if (item->getType() == "Scroll") {
      std::string effect = std::get<std::string>(item->getSpecParam());
      effect_count[effect]++;
    }
  }

  if (effect_count.empty()) {
    std::cout << "- Scrolls: not available" << std::endl;
  } else {
    std::string most_frequent;
    int max_count = 0;
    for (const auto& pair : effect_count) {
      if (pair.second > max_count) {
        max_count = pair.second;
        most_frequent = pair.first;
      }
    }
    std::cout << "- Scrolls: most frequent effect " << most_frequent
              << std::endl;
  }
}
