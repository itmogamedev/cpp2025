#include <clocale>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "classes.h"
#ifdef _WIN32
#include <windows.h>
#endif

class OneItem {
 public:
  std::string type;
  std::string name;
  int price;
  double weight;
  std::string spec_param;
};

class Shop {
 public:
  std::string name;
  std::vector<OneItem> items;
  void clear() {
    name.clear();
    items.clear();
  }
};

std::vector<Shop> file() {
  std::ifstream file("shops.txt");
  std::string line;
  std::vector<Shop> shops;
  Shop thisShop;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line.find("Магазин:") == 0) {
      if (!thisShop.name.empty()) {
        shops.push_back(thisShop);
      }
      thisShop = Shop();
      thisShop.name = line.substr(line.find(":") + 2);
    } else if (line.find("Предметы:") == 0) {
      continue;
    } else {
      std::istringstream stream(line);
      OneItem item;
      if (stream >> item.type >> item.name >> item.price >> item.weight >>
          item.spec_param) {
        thisShop.items.push_back(item);
      }
    }
  }

  if (!thisShop.name.empty()) {
    shops.push_back(thisShop);
  }

  return shops;
}

int main() {
  auto shops = file();
  #ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_ALL, "Russian");
  #endif

  for (const auto& shop : shops) {
    double priceSum = 0;
    double weightSum = 0;

    std::vector<Weapon> shopWeapons;
    std::vector<Armor> shopArmors;
    std::vector<Potion> shopPotions;
    std::vector<Scroll> shopScrolls;

    for (const auto& item : shop.items) {
      priceSum += item.price;
      weightSum += item.weight;

      if (item.type == "Оружие") {
        int damage = std::stoi(item.spec_param);
        shopWeapons.push_back(
            Weapon(item.name, item.price, item.weight, damage));
      } else if (item.type == "Броня") {
        int defence = std::stoi(item.spec_param);
        shopArmors.push_back(
            Armor(item.name, item.price, item.weight, defence));
      } else if (item.type == "Зелье") {
        double duration = std::stod(item.spec_param);
        shopPotions.push_back(
            Potion(item.name, item.price, item.weight, duration));
      } else if (item.type == "Свиток") {
        shopScrolls.push_back(
            Scroll(item.name, item.price, item.weight, item.spec_param));
      }
    }

    std::cout << "\n\n=== Магазин: " << shop.name << " ===" << std::endl;
    std::cout << "Всего предметов: " << shop.items.size() << std::endl;
    std::cout << "Средняя цена: " << priceSum / shop.items.size() << std::endl;
    std::cout << "Средний вес: " << weightSum / shop.items.size() << "\n";
    std::cout << "\nСтатистика по предметам:" << std::endl;

    if (!shopWeapons.empty()) {
      double damage_sum = 0;
      for (const auto& weapon : shopWeapons) {
        auto param = weapon.getSpecParam();
        damage_sum += std::get<int>(param);
      }
      std::cout << "Оружие: средний урон = " << damage_sum / shopWeapons.size()
                << std::endl;
    } else {
      std::cout << "Оружие: нет в наличии" << std::endl;
    }

    if (!shopArmors.empty()) {
      double defence_sum = 0;
      for (const auto& armor : shopArmors) {
        auto param = armor.getSpecParam();
        defence_sum += std::get<int>(param);
      }
      std::cout << "Броня: средняя защита = "
                << defence_sum / shopArmors.size() << std::endl;
    } else {
      std::cout << "Броня: нет в наличии" << std::endl;
    }

    if (!shopPotions.empty()) {
      double duration_sum = 0;
      for (const auto& potion : shopPotions) {
        auto param = potion.getSpecParam();
        duration_sum += std::get<double>(param);
      }
      std::cout << "Зелья: средняя длительность = "
                << duration_sum / shopPotions.size() << std::endl;
    } else {
      std::cout << "Зелья: нет в наличии" << std::endl;
    }

    if (!shopScrolls.empty()) {
      std::map<std::string, int> effect_count;
      for (const auto& scroll : shopScrolls) {
        auto param = scroll.getSpecParam();
        std::string effect = std::get<std::string>(param);
        effect_count[effect]++;
      }

      std::vector<std::string> most_common_effects;
      int max_count = 0;
      for (const auto& [effect, count] : effect_count) {
        if (count > max_count) {
          max_count = count;
        }
      }
      for (const auto& [effect, count] : effect_count) {
        if (count == max_count) {
          most_common_effects.push_back(effect);
        }
      }
      if (most_common_effects.size() == 1) {
        std::cout << "Свитки: самый частый эффект = " << most_common_effects[0]
                  << std::endl;
      } else {
        std::cout << "Свитки: самые частые эффекты: \n";
        for (int i = 0; i < most_common_effects.size(); i++) {
          std::cout << most_common_effects[i] << "\n";
        }
      }
    }
  }

  return 0;
}