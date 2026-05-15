#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "magic_items.h"

std::vector<Shop*> loadShopsFromFile(const std::string& filename) {
  std::vector<Shop*> shops;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return shops;
  }

  std::string line;
  Shop* current_shop = nullptr;
  int items_to_read = 0;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    std::istringstream iss(line);
    std::string keyword;
    iss >> keyword;

    if (keyword == "Магазин:") {
      std::string shop_name;
      iss >> shop_name;
      current_shop = new Shop(shop_name);
      shops.push_back(current_shop);
    } else if (keyword == "Предметы:") {
      iss >> items_to_read;
    } else if (current_shop != nullptr && items_to_read > 0) {
      std::string type, name;
      double price, weight;

      type = keyword;
      iss >> name >> price >> weight;

      MagicItem* item = nullptr;

      if (type == "Оружие") {
        int damage;
        iss >> damage;
        item = new Weapon(name, price, weight, damage);
      } else if (type == "Броня") {
        int defense;
        iss >> defense;
        item = new Armor(name, price, weight, defense);
      } else if (type == "Зелье") {
        double duration;
        iss >> duration;
        item = new Potion(name, price, weight, duration);
      } else if (type == "Свиток") {
        std::string effect;
        iss >> effect;
        item = new Scroll(name, price, weight, effect);
      }

      if (item != nullptr) {
        current_shop->addItem(item);
        items_to_read--;
      }
    }
  }

  file.close();
  return shops;
}

int main() {
  std::vector<Shop*> shops = loadShopsFromFile("magic_items.txt");

  if (shops.empty()) {
    std::cout << "Не удалось загрузить данные о магазинах." << std::endl;
    return 1;
  }

  for (const auto& shop : shops) {
    std::cout << "=== Магазин: " << shop->getName() << " ===" << std::endl;
    std::cout << "Всего предметов: " << shop->getItems().size() << std::endl;

    std::cout << "Средняя цена: " << std::fixed << std::setprecision(2)
              << shop->calculateAveragePrice() << " золота" << std::endl;

    std::cout << "Средний вес: " << std::fixed << std::setprecision(2)
              << shop->calculateAverageWeight() << " кг" << std::endl;

    std::cout << std::endl;
    std::cout << "Статистика по предметам:" << std::endl;
    shop->analyzeSpecificParams();
    std::cout << std::endl;
  }

  // Очистка памяти
  for (auto shop : shops) {
    delete shop;
  }

  return 0;
}
