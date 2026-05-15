#include <Windows.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Shop.h"

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  std::vector<Shop*> shops_container;
  std::ifstream in("shops.txt");
  if (in.is_open()) {
    std::string line;
    while (std::getline(in, line)) {
      if (line == "") continue;
      Shop* currShop = new Shop(line.substr(line.find(": ") + 2));
      shops_container.push_back(currShop);
      std::getline(in, line);
      int itemsAmount = std::stoi(line.substr(line.find(": ") + 2));
      for (int i = 0; i < itemsAmount; i++) {
        std::getline(in, line);
        std::string type;
        std::string name;
        int price;
        double weight;
        std::string specialParam;

        int fieldIndex = 0;
        std::string currentField;
        for (char c : line) {
          if (c == ' ') {
            switch (fieldIndex) {
              case 0:
                type = currentField;
                break;
              case 1:
                name = currentField;
                break;
              case 2:
                price = std::stoi(currentField);
                break;
              case 3:
                weight = std::stod(currentField);
                break;
            }
            currentField.clear();
            fieldIndex++;
          } else {
            currentField += c;
          }
        }
        specialParam = currentField;
        currShop->addItem(type, name, price, weight, specialParam);
      }
    }
  }
  for (auto shop : shops_container) {
    std::cout << "=== Магазин: " << shop->getName() << " ===\n"
              << "Всего предметов: " << shop->getItemsAmount() << "\n"
              << "Средняя цена: " << shop->avgPrice() << " золота\n"
              << "Средний вес: " << shop->avgWeight() << " кг\n\n"
              << "Статистика по предметам:\n"
              << "- Оружие: ";
    double avgDamage = shop->avgParam("Weapon");
    if (avgDamage == 0)
      std::cout << "нет в наличии\n";
    else
      std::cout << "средний урон = " << avgDamage << "\n";

    std::cout << "- Броня: ";
    double avgDefense = shop->avgParam("Armor");
    if (avgDefense == 0)
      std::cout << "нет в наличии\n";
    else
      std::cout << "средняя защита = " << avgDefense << "\n";

    std::cout << "- Зелья: ";
    double avgDuration = shop->avgParam("Potion");
    if (avgDuration == 0)
      std::cout << "нет в наличии\n";
    else
      std::cout << "средняя длительность = " << avgDuration << "\n";

    std::cout << "- Свитки: ";
    std::string avgScroll = shop->avgScroll();
    if (avgScroll == "")
      std::cout << "нет в наличии\n\n";
    else
      std::cout << "самый частый эффект: " << avgScroll << "\n\n";
  }
}
