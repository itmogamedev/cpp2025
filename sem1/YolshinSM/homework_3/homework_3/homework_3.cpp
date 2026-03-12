#include <windows.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Armor.h"
#include "MagicItem.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

struct Shop {
  std::string name;
  int items_count;
  std::vector<Weapon> items_weapon;
  std::vector<Armor> items_armor;
  std::vector<Scroll> items_scroll;
  std::vector<Potion> items_potion;
};
std::vector<Shop> shops;
std::vector<Shop> readShopsFromFile(std::string filename) {
  std::ifstream file(filename);
  std::string line;

  Shop current_shop;
  int items_to_read = 0;

  auto save_shop = [&]() {
    if (!current_shop.name.empty()) {
      shops.push_back(std::move(current_shop));
      current_shop = Shop();
    }
  };

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line.find("Магазин:") == 0) {
      save_shop();
      current_shop.name = line.substr(8);
      current_shop.name.erase(0, current_shop.name.find_first_not_of(" \t"));
    } else if (line.find("Предметы:") == 0) {
      items_to_read = std::stoi(line.substr(9));
      current_shop.items_count = items_to_read;
    } else if (items_to_read > 0) {
      std::istringstream iss(line);
      std::string type, name;
      int price;
      double weight;
      std::string special_param;
      iss.imbue(std::locale("C"));
      iss >> type >> name >> price >> weight;

      std::getline(iss, special_param);
      special_param.erase(0, special_param.find_first_not_of(" \t"));
      if (type == "Оружие") {
        current_shop.items_weapon.push_back(
            Weapon(name, price, weight, std::stoi(special_param)));
      } else if (type == "Броня") {
        current_shop.items_armor.push_back(
            Armor(name, price, weight, std::stoi(special_param)));
      } else if (type == "Зелье") {
        current_shop.items_potion.push_back(
            Potion(name, price, weight, std::stod(special_param)));
      } else if (type == "Свиток") {
        current_shop.items_scroll.push_back(
            Scroll(name, price, weight, special_param));
      }
      items_to_read--;
    }
  }

  save_shop();
  return shops;
}
std::string getMostFrequent(std::vector<std::string>& strings) {
  std::unordered_map<std::string, int> counts;
  for (const auto& str : strings) {
    counts[str]++;
  }

  return std::max_element(
             counts.begin(), counts.end(),
             [](const auto& a, const auto& b) { return a.second < b.second; })
      ->first;
}
void printShops() {
  for (Shop shop : shops) {
    double all_price = 0;
    double all_weight = 0;
    double all_damage = 0;
    double all_defense = 0;
    double all_duration = 0;
    std::vector<std::string> all_effect;
    for (Weapon weapon : shop.items_weapon) {
      all_damage += std::get<0>(weapon.getSpecParam());
      all_price += weapon.getPrice();
      all_weight += weapon.getWeight();
    }
    for (Armor armor : shop.items_armor) {
      all_defense += std::get<0>(armor.getSpecParam());
      all_price += armor.getPrice();
      all_weight += armor.getWeight();
    }
    for (Potion potion : shop.items_potion) {
      all_duration += std::get<1>(potion.getSpecParam());
      all_price += potion.getPrice();
      all_weight += potion.getWeight();
    }
    for (Scroll scroll : shop.items_scroll) {
      all_effect.push_back(std::get<2>(scroll.getSpecParam()));
      all_price += scroll.getPrice();
      all_weight += scroll.getWeight();
    }
    std::cout << "=== Магазин: " << shop.name << " ===" << '\n';
    std::cout << "Всего предметов: " << shop.items_count << '\n';
    std::cout << "Средняя цена: " << all_price / shop.items_count << " Денюжек"
              << '\n';
    std::cout << "Средний вес: " << all_weight / shop.items_count << " Кг."
              << '\n'
              << '\n';
    std::cout << "Статистика по предметам:" << '\n';
    (all_damage > 0 ? std::cout << "- Оружие: средний урон = "
                                << (all_damage / shop.items_weapon.size())
                    : std::cout << "- Оружие: нет в наличии")
        << '\n';
    (all_defense > 0 ? std::cout << "- Броня: средняя защита = "
                                 << (all_defense / shop.items_armor.size())
                     : std::cout << "- Броня: нет в наличии")
        << '\n';
    (all_duration > 0 ? std::cout << "- Зелья: средняя длительность = "
                                  << (all_duration / shop.items_potion.size())
                      : std::cout << "- Зелья: нет в наличии")
        << '\n';
    (all_effect.size() > 0 ? std::cout << "- Свитки: самый частый эффект "
                                       << getMostFrequent(all_effect)
                           : std::cout << "- Свитки: нет в наличии")
        << '\n';
    std::cout << "________________________________" << '\n';
  }
}
int main() {
  SetConsoleOutputCP(1251);
  std::vector<Shop> shops = readShopsFromFile("shops.txt");
  printShops();
}
