#include <iostream>
#include <map>

#include "armor.h"
#include "potion.h"
#include "scroll.h"
#include "shop.h"
#include "weapon.h"

void Shop::addItem(std::unique_ptr<MagicItem> item) {
  items.push_back(std::move(item));
}

int Shop::getItemCount() const { return static_cast<int>(items.size()); }

double Shop::getAveragePrice() const {
  if (items.empty()) {
    return 0.0;
  }
  long long sum = 0;
  for (const auto& item : items) {
    sum += item->getPrice();
  }
  return static_cast<double>(sum) / items.size();
}

double Shop::getAverageWeight() const {
  if (items.empty()) {
    return 0.0;
  }
  double sum = 0.0;
  for (const auto& item : items) {
    sum += item->getWeight();
  }
  return sum / items.size();
}

void Shop::printStats() const {
  std::cout << "=== Магазин: " << name << " ===\n";
  std::cout << "Всего предметов: " << getItemCount() << "\n";
  std::cout << "Средняя цена: " << getAveragePrice() << " золота\n";
  std::cout << "Средний вес: " << getAverageWeight() << " кг\n\n";

  std::cout << "Статистика по предметам:\n";

  // Для int/double – среднее, для string – самый частый.
  struct TypeStats {
    int count = 0;
    long long sum_int = 0;
    double sum_double = 0.0;
    std::map<std::string, int> string_freq;
  };

  std::map<std::string, TypeStats> stats;

  for (const auto& item : items) {
    std::string type = item->getTypeName();
    auto& st = stats[type];
    st.count += 1;
    auto param = item->getSpecParam();
    if (std::holds_alternative<int>(param)) {
      st.sum_int += std::get<int>(param);
    } else if (std::holds_alternative<double>(param)) {
      st.sum_double += std::get<double>(param);
    } else if (std::holds_alternative<std::string>(param)) {
      const std::string& value = std::get<std::string>(param);
      st.string_freq[value] += 1;
    }
  }

  auto printType = [&](const std::string& type, const std::string& label,
                       const std::string& unit) {
    auto it = stats.find(type);
    if (it == stats.end() || it->second.count == 0) {
      std::cout << "- " << label << ": нет в наличии\n";
      return;
    }
    const TypeStats& st = it->second;
    if (!st.string_freq.empty()) {
      // Для Scroll: самый частый эффект.
      std::string best_effect;
      int best_count = 0;
      for (const auto& pair : st.string_freq) {
        if (pair.second > best_count) {
          best_count = pair.second;
          best_effect = pair.first;
        }
      }
      std::cout << "- " << label << ": самый частый эффект = " << best_effect
                << "\n";
    } else if (st.sum_int != 0) {
      double avg = static_cast<double>(st.sum_int) / st.count;
      std::cout << "- " << label << ": средний " << unit << " = " << avg
                << "\n";
    } else {
      double avg = st.sum_double / st.count;
      std::cout << "- " << label << ": средняя " << unit << " = " << avg
                << "\n";
    }
  };

  printType("Weapon", "Оружие", "урон");
  printType("Armor", "Броня", "защита");
  printType("Potion", "Зелья", "длительность");
  printType("Scroll", "Свитки", "параметр");

  std::cout << "\n";
}
