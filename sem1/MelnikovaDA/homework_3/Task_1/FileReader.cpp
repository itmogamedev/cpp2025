#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

std::vector<shop> fileReader::readShopsFromFile(const std::string& file_name) {
  std::vector<shop> shops;
  std::ifstream file(file_name);
  std::string line;

  if (!file.is_open()) {
    std::cout << "Ошибка: не удалось открыть файл " << file_name << std::endl;
    return shops;
  }

  shop* current_Shop = nullptr;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line.find("Магазин:") != std::string::npos) {
      std::string shop_Name = line.substr(line.find(":") + 2);
      shops.emplace_back(shop_Name);
      current_Shop = &shops.back();
    } else if (line.find("Предметы:") != std::string::npos) {
      continue;
    } else if (current_Shop != nullptr) {
      std::istringstream iss(line);
      std::string type, name;
      int price;
      double weight;
      std::string spec_Param;

      iss >> type >> name >> price >> weight >> spec_Param;

      if (type == "Оружие") {
        int damage = std::stoi(spec_Param);
        current_Shop->addItem(
            std::make_unique<weapon>(name, price, weight, damage));
      } else if (type == "Броня") {
        int defense = std::stoi(spec_Param);
        current_Shop->addItem(
            std::make_unique<armor>(name, price, weight, defense));
      } else if (type == "Зелье") {
        double duration = std::stod(spec_Param);
        current_Shop->addItem(
            std::make_unique<potion>(name, price, weight, duration));
      } else if (type == "Свиток") {
          current_Shop->addItem(
            std::make_unique<scroll>(name, price, weight, spec_Param));
      }
    }
  }

  file.close();
  return shops;
}
