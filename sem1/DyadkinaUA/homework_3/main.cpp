#include <windows.h>

#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <string>

#include "armor.h"
#include "potion.h"
#include "scroll.h"
#include "shop.h"
#include "weapon.h"

int main() {
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  std::ifstream input("shops.txt");
  if (!input.is_open()) {
    std::cout << "Не удалось открыть файл shops.txt\n";
    return 1;
  }

  std::vector<Shop> shops;

  while (true) {
    std::string word;
    if (!(input >> word)) {
      break;
    }
    if (word != "Магазин:") {
      break;
    }

    std::string shop_name;
    input >> shop_name;
    Shop shop(shop_name);

    std::string items_label;
    int item_count = 0;
    input >> items_label >> item_count;  // "Предметы:" N

    for (int i = 0; i < item_count; ++i) {
      std::string type;
      std::string name;
      int price = 0;
      double weight = 0.0;
      input >> type >> name >> price >> weight;

      if (type == "Оружие") {
        int damage = 0;
        input >> damage;
        shop.addItem(std::make_unique<Weapon>(name, price, weight, damage));
      } else if (type == "Броня") {
        int defense = 0;
        input >> defense;
        shop.addItem(std::make_unique<Armor>(name, price, weight, defense));
      } else if (type == "Зелье") {
        double duration = 0.0;
        input >> duration;
        shop.addItem(std::make_unique<Potion>(name, price, weight, duration));
      } else if (type == "Свиток") {
        std::string effect;
        input >> effect;
        shop.addItem(std::make_unique<Scroll>(name, price, weight, effect));
      }
    }

    shops.push_back(std::move(shop));
  }

  for (const auto& shop : shops) {
    shop.printStats();
  }

  return 0;
}
