#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "MagicItem.h"

std::vector<Shop> readShopsFromFile(const std::string& filename) {
  std::vector<Shop> shops;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Error: Cannot open file " << filename << std::endl;
    return shops;
  }

  std::string line;

  while (std::getline(file, line)) {
    if (line.find("Shop:") == 0) {
      std::string shopName = line.substr(6);
      shops.emplace_back(shopName);

      if (!std::getline(file, line)) break;

      int itemCount = 0;
      if (line.find("Items:") == 0) {
        itemCount = std::stoi(line.substr(7));
      }

      for (int i = 0; i < itemCount; ++i) {
        if (!std::getline(file, line)) break;

        std::stringstream ss(line);
        std::string type, name, specParam;
        int price;
        double weight;

        ss >> type >> name >> price >> weight >> specParam;

        if (type == "Weapon") {
          shops.back().addItem(std::unique_ptr<Weapon>(
              new Weapon(name, price, weight, std::stoi(specParam))));
        } else if (type == "Armor") {
          shops.back().addItem(std::unique_ptr<Armor>(
              new Armor(name, price, weight, std::stoi(specParam))));
        } else if (type == "Potion") {
          shops.back().addItem(std::unique_ptr<Potion>(
              new Potion(name, price, weight, std::stod(specParam))));
        } else if (type == "Scroll") {
          shops.back().addItem(std::unique_ptr<Scroll>(
              new Scroll(name, price, weight, specParam)));
        }
      }
    }
  }

  file.close();
  return shops;
}

int main() {
  auto shops = readShopsFromFile("shops_data.txt");
  for (const auto& shop : shops) shop.analyzeShop();
  return 0;
}
