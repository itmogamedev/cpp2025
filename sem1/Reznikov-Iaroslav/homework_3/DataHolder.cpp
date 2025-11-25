#include "DataHolder.h"

#include <fstream>
#include <sstream>
#include <string>

#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

DataHolder::DataHolder(const std::string& fileName) { loadFromFile(fileName); }

void DataHolder::loadFromFile(const std::string& fileName) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + fileName);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("Shop:") != std::string::npos) {
      size_t colonPos = line.find(':');
      std::string shopName = line.substr(colonPos + 2);
      auto shop = std::make_unique<Shop>(shopName);
      std::getline(file, line);

      while (std::getline(file, line) && !line.empty()) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        std::unique_ptr<MagicItem> item;

        if (type == WEAPON_STR) {
          item = std::make_unique<Weapon>(ss);
        } else if (type == ARMOR_STR) {
          item = std::make_unique<Armor>(ss);
        } else if (type == POTION_STR) {
          item = std::make_unique<Potion>(ss);
        } else if (type == SCROLL_STR) {
          item = std::make_unique<Scroll>(ss);
        }

        if (item) {
          shop->addItem(std::move(item));
        }
      }

      shops.push_back(std::move(shop));
    }
  }

  file.close();
}
