#include "shop.h"

#include <iostream>
#include <map>
#include <numeric>

Shop::Shop(const std::string& name) : name(name) {}

void Shop::addItem(std::unique_ptr<MagicItem> item) {
  items.push_back(std::move(item));
}

double Shop::averagePrice() const {
  if (items.empty()) {
    return 0.0;
  }

  int sum = 0;
  for (const auto& item : items) {
    sum += item->getPrice();
  }

  return double(sum) / items.size();
}

double Shop::averageWeight() const {
  if (items.empty()) {
    return 0.0;
  }

  double sum = 0.0;
  for (const auto& item : items) {
    sum += item->getWeight();
  }
  return sum / items.size();
}

void Shop::printTypeStats() const {
  int weapon_count = 0;
  int weapon_damage_sum = 0;

  int armor_count = 0;
  int armor_defense_sum = 0;

  int potion_count = 0;
  double potion_duration_sum = 0.0;

  int scroll_count = 0;
  std::map<std::string, int> scroll_effects;

  for (const auto& item : items) {
    if (const auto* weapon = dynamic_cast<const Weapon*>(item.get())) {
      weapon_count++;
      weapon_damage_sum += std::get<int>(weapon->getSpecParam());
    } else if (const auto* armor = dynamic_cast<const Armor*>(item.get())) {
      armor_count++;
      armor_defense_sum += std::get<int>(armor->getSpecParam());
    } else if (const auto* potion = dynamic_cast<const Potion*>(item.get())) {
      potion_count++;
      potion_duration_sum += std::get<double>(potion->getSpecParam());
    } else if (const auto* scroll = dynamic_cast<const Scroll*>(item.get())) {
      scroll_count++;
      SpecParam scroll_param = scroll->getSpecParam();
      const std::string& effect = std::get<std::string>(scroll_param);
      scroll_effects[effect]++;
    }
  }

  std::cout << "Статистика по предметам:\n";

  if (weapon_count > 0) {
    double average_damage = (double)(weapon_damage_sum) / weapon_count;
    std::cout << "- Оружие: средний урон = " << average_damage << "\n";
  } else {
    std::cout << "- Оружие: нет в наличии\n";
  }

  if (armor_count > 0) {
    double average_defense = (double)(armor_defense_sum) / armor_count;
    std::cout << "- Броня: средняя защита = " << average_defense << "\n";
  } else {
    std::cout << "- Броня: нет в наличии\n";
  }

  if (potion_count > 0) {
    double average_duration = (double)(potion_duration_sum) / potion_count;
    std::cout << "- Зелья: средняя длительность = " << average_duration << "\n";
  } else {
    std::cout << "- Зелья: нет в наличии\n";
  }

  if (scroll_count > 0) {
    std::string very_best_top_effect;
    int best_count = 0;
    for (const auto& [effect, count] : scroll_effects) {
      if (count > best_count) {
        best_count = count;
        very_best_top_effect = effect;
      }
    }
    std::cout << "- Свитки: самый частый эффект " << very_best_top_effect
              << "\n";
  } else {
    std::cout << "- Свитки: нет в наличии\n";
  }
}

void Shop::printReport() const {
  std::cout << "=== Магазин: " << name << " ===\n";
  std::cout << "Всего предметов: " << items.size() << "\n";
  std::cout << "Средняя цена: " << averagePrice() << " золота\n";
  std::cout << "Средний вес: " << averageWeight() << "кг \n\n";

  printTypeStats();
  std::cout << "\n";
}
