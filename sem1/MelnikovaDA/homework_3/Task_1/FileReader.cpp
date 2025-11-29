#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

std::vector<Shop> FileReader::readShopsFromFile(const std::string& filename) {
  std::vector<Shop> shops;
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return shops;
  }

  Shop* currentShop = nullptr;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line.find("Магазин:") != std::string::npos) {
      std::string shopName = line.substr(line.find(":") + 2);
      shops.emplace_back(shopName);
      currentShop = &shops.back();
    } else if (line.find("Предметы:") != std::string::npos) {
      continue;
    } else if (currentShop != nullptr) {
      std::istringstream iss(line);
      std::string type, name;
      int price;
      double weight;
      std::string specParam;

      iss >> type >> name >> price >> weight >> specParam;

      if (type == "Оружие") {
        int damage = std::stoi(specParam);
        currentShop->addItem(
            std::make_unique<Weapon>(name, price, weight, damage));
      } else if (type == "Броня") {
        int defense = std::stoi(specParam);
        currentShop->addItem(
            std::make_unique<Armor>(name, price, weight, defense));
      } else if (type == "Зелье") {
        double duration = std::stod(specParam);
        currentShop->addItem(
            std::make_unique<Potion>(name, price, weight, duration));
      } else if (type == "Свиток") {
        currentShop->addItem(
            std::make_unique<Scroll>(name, price, weight, specParam));
      }
    }
  }

  file.close();
  return shops;
}
