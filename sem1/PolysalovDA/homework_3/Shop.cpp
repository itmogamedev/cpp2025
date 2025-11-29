#include "Shop.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

Shop::Shop(const std::string& n) : name(n) {}

Shop::~Shop() {
  for (auto item : items) {
    delete item;
  }
}

void Shop::addItem(MagicItem* item) { items.push_back(item); }

double Shop::getAveragePrice() const {
  if (items.empty()) return 0.0;
  double sum = 0;
  for (const auto& item : items) {
    sum += item->getPrice();
  }
  return sum / items.size();
}

double Shop::getAverageWeight() const {
  if (items.empty()) return 0.0;
  double sum = 0;
  for (const auto& item : items) {
    sum += item->getWeight();
  }
  return sum / items.size();
}

void Shop::printSpecParamStats() const {
  std::map<std::string, std::vector<std::variant<int, double, std::string>>>
      type_params;

  for (const auto& item : items) {
    type_params[item->getType()].push_back(item->getSpecParam());
  }

  std::vector<std::string> all_types = {"оружие", "защита", "скрепы", "грибы"};

  for (const auto& type : all_types) {
    std::cout << "- " << type << ": ";

    if (type_params.find(type) == type_params.end()) {
      std::cout << "нет в наличии" << std::endl;
      continue;
    }

    const auto& params = type_params[type];

    if (type == "оружие" || type == "защита") {
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<int>(param);
      }
      if (type == "оружие") {
        std::cout << "средний урон = " << std::fixed << std::setprecision(0)
                  << sum / params.size() << std::defaultfloat;
      } else {
        std::cout << "средняя защита = " << std::fixed << std::setprecision(0)
                  << sum / params.size() << std::defaultfloat;
      }
    } else if (type == "скрепы" || type == "грибы") {
      std::map<std::string, int> frequency;
      for (const auto& param : params) {
        frequency[std::get<std::string>(param)]++;
      }

      std::string most_common;
      int max_count = 0;
      for (const auto& [effect, count] : frequency) {
        if (count > max_count) {
          max_count = count;
          most_common = effect;
        }
      }

      if (type == "скрепы") {
        std::cout << "самый частый эффект " << most_common;
      } else {
        std::cout << "самая частая рыгучесть " << most_common;
      }
    }
    std::cout << std::endl;
  }
}

void Shop::printStats() const {
  std::cout << "=== Магазин: " << name << " ===" << std::endl;
  std::cout << "Всего предметов: " << items.size() << std::endl;
  std::cout << "Средняя цена: " << std::fixed << std::setprecision(2)
            << getAveragePrice() << " золота" << std::endl;
  std::cout << "Средний вес: " << std::fixed << std::setprecision(2)
            << getAverageWeight() << " кг" << std::endl;
  std::cout << std::endl << "Статистика по предметам:" << std::endl;
  printSpecParamStats();
  std::cout << std::endl;
}