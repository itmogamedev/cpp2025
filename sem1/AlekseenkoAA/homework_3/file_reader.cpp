#include "file_reader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<Shop> readShopsFromFile(const std::string& filename) {
  std::ifstream input(filename);
  if (!input.is_open()) {
    throw std::runtime_error("Не удалось открыть файл: " + filename);
  }

  std::vector<Shop> shops;
  std::string line;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    std::string shop_name = line.substr(std::string("Магазин:").size());

    if (!shop_name.empty() && shop_name[0] == ' ') {
      shop_name.erase(0, 1);
    }

    Shop shop(shop_name);

    // строка предметов
    if (!std::getline(input, line)) {
      break;
    }

    std::istringstream items_stream(line);
    std::string items_label;
    int items_count = 0;
    items_stream >> items_label >> items_count;

    for (int i = 0; i < items_count; ++i) {
      if (!std::getline(input, line)) {
        break;
      }

      std::istringstream item_stream(line);
      std::string type;
      std::string name;
      int price = 0;
      double weight = 0.0;

      item_stream >> type >> name >> price >> weight;

      if (type == "Оружие") {
        int damage = 0;
        item_stream >> damage;
        auto item = std::make_unique<Weapon>(name, price, weight, damage);
        shop.addItem(std::move(item));
      } else if (type == "Броня") {
        int defense = 0;
        item_stream >> defense;
        auto item = std::make_unique<Armor>(name, price, weight, defense);
        shop.addItem(std::move(item));
      } else if (type == "Зелье") {
        double duration = 0.0;
        item_stream >> duration;
        auto item = std::make_unique<Potion>(name, price, weight, duration);
        shop.addItem(std::move(item));
      } else if (type == "Свиток") {
        std::string effect;
        item_stream >> effect;
        auto item = std::make_unique<Scroll>(name, price, weight, effect);
        shop.addItem(std::move(item));
      }
    }

    shops.push_back(std::move(shop));
  }

  return shops;
}
