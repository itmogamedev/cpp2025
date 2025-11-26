#include <fstream>
#include <iostream>
#include <sstream>

#include "armor.h"
#include "file_reader.h"
#include "potion.h"
#include "scroll.h"
#include "weapon.h"

std::vector<Shop> FileReader::readFromFile(const std::string& filename) {
  std::vector<Shop> shops;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return shops;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("Shop:") != std::string::npos) {
      std::string shop_name = line.substr(line.find(":") + 2);
      Shop shop(shop_name);

      std::getline(file, line);  // Read line with item count

      while (std::getline(file, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string type, name;
        int price;
        double weight;

        iss >> type >> name >> price >> weight;

        if (type == "Weapon") {
          int damage;
          iss >> damage;
          shop.addItem(std::make_shared<Weapon>(name, price, weight, damage));
        } else if (type == "Armor") {
          int defense;
          iss >> defense;
          shop.addItem(std::make_shared<Armor>(name, price, weight, defense));
        } else if (type == "Potion") {
          double duration;
          iss >> duration;
          shop.addItem(std::make_shared<Potion>(name, price, weight, duration));
        } else if (type == "Scroll") {
          std::string effect;
          iss >> effect;
          shop.addItem(std::make_shared<Scroll>(name, price, weight, effect));
        }
      }

      shops.push_back(shop);
    }
  }

  file.close();
  return shops;
}
