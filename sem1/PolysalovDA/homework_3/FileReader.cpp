#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "DerivedItems.h"

MagicItem* createItem(const std::string& type, const std::string& name,
                      int price, double weight, const std::string& specParam) {
  if (type == "оружие") {
    return new Weapon(name, price, weight, std::stoi(specParam));
  } else if (type == "защита") {
    return new Armor(name, price, weight, std::stoi(specParam));
  } else if (type == "скрепы") {
    return new Brace(name, price, weight, specParam);
  } else if (type == "грибы") {
    return new Mushroom(name, price, weight, specParam);
  }
  return nullptr;
}

std::vector<Shop*> readShopsFromFile(const std::string& filename) {
  std::vector<Shop*> shops;
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
    return shops;
  }

  Shop* currentShop = nullptr;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line == "*") {
      if (currentShop) {
        shops.push_back(currentShop);
        currentShop = nullptr;
      }
      continue;
    }

    if (line == "=") continue;

    if (currentShop == nullptr) {
      size_t commaPos = line.find(',');
      if (commaPos != std::string::npos) {
        std::string shopName = line.substr(0, commaPos);
        currentShop = new Shop(shopName);
      }
    } else {
      std::istringstream iss(line);
      std::string type, name, specParam;
      int price;
      double weight;
      char delimiter;

      if (std::getline(iss, type, ';') && std::getline(iss, name, ';') &&
          (iss >> price) && (iss >> delimiter) && delimiter == ';' &&
          (iss >> weight) && (iss >> delimiter) && delimiter == ';' &&
          std::getline(iss, specParam)) {
        type.erase(0, type.find_first_not_of(" \t"));
        type.erase(type.find_last_not_of(" \t") + 1);
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        specParam.erase(0, specParam.find_first_not_of(" \t"));
        specParam.erase(specParam.find_last_not_of(" \t") + 1);

        MagicItem* item = createItem(type, name, price, weight, specParam);
        if (item) {
          currentShop->addItem(item);
        }
      }
    }
  }

  if (currentShop) {
    shops.push_back(currentShop);
  }

  file.close();
  return shops;
}