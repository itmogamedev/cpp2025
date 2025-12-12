#include "parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "items.h"

std::vector<Shop> Parser::parseFile(const std::string& filename) {
  std::vector<Shop> shops;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
    return shops;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("Магазин:") == 0) {
      std::string shop_name = line.substr(8);
      Shop shop(shop_name);

      if (!std::getline(file, line)) break;
      if (line.find("Предметы:") != 0) {
        std::cerr << "Ошибка формата файла: ожидалось 'Предметы:'\n";
        continue;
      }

      size_t colon_pos = line.find(':');
      int item_count = std::stoi(line.substr(colon_pos + 1));

      for (int i = 0; i < item_count && std::getline(file, line); ++i) {
        if (line.empty()) continue;

        std::istringstream stream(line);
        std::string item_type, item_name;
        int item_price;
        double item_weight;
        std::string special_param;

        stream >> item_type >> item_name >> item_price >> item_weight;
        std::replace(item_name.begin(), item_name.end(), '_', ' ');

        stream >> special_param;

        if (item_type == "Оружие") {
          int damage = std::stoi(special_param);
          shop.addItem(std::make_unique<Weapon>(item_name, item_price,
                                                item_weight, damage));
        } else if (item_type == "Броня") {
          int defense = std::stoi(special_param);
          shop.addItem(std::make_unique<Armor>(item_name, item_price,
                                               item_weight, defense));
        } else if (item_type == "Зелье") {
          double duration = std::stod(special_param);
          shop.addItem(std::make_unique<Potion>(item_name, item_price,
                                                item_weight, duration));
        } else if (item_type == "Свиток") {
          std::replace(special_param.begin(), special_param.end(), '_', ' ');
          shop.addItem(std::make_unique<Scroll>(item_name, item_price,
                                                item_weight, special_param));
        }
      }

      shops.push_back(std::move(shop));
    }
  }

  file.close();
  return shops;
}
