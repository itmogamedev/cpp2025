#include <clocale>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

#ifdef _WIN32
#include <windows.h>
#endif

struct OneItem {
  std::string type;
  std::string name;
  int price;
  double weight;
  std::string specParam;
};

struct Shop {
  std::string name;
  std::vector<OneItem> items;
  void clear() {
    name.clear();
    items.clear();
  }
};

std::vector<Shop> createShopsData() {
  std::vector<Shop> shops;

  Shop shop1;
  shop1.name = "Чердачный_кладезь";
  shop1.items = {
      {"Оружие", "Соседская_крапива", 500, 0.2, "60"},
      {"Оружие", "Хохолок_свиристели", 600, 0.1, "50"},
      {"Оружие", "Куриные_ядра", 300, 0.2, "30"},
      {"Зелье", "Настойка_Бабы_Яги", 1000, 0.2, "90.0"},
      {"Зелье", "Топлёный_холодец", 400, 0.3, "50.4"},
      {"Свиток", "Проклятье_на_татарском", 900, 0.2, "Речевая_татрофия"}};
  shops.push_back(shop1);

  Shop shop2;
  shop2.name = "Антикварное_подполье";
  shop2.items = {{"Броня", "Стеклянная_кольчуга", 1000, 2.4, "40"},
                 {"Броня", "Половинка_яйца_фаберже", 500, 0.9, "30"},
                 {"Оружие", "Подложечка_для_кофе", 400, 0.1, "40"},
                 {"Оружие", "Ручка_стула", 300, 0.3, "39"},
                 {"Зелье", "Вода_из-под_гуся", 600, 0.6, "30.8"},
                 {"Свиток", "Ветхий_привет", 800, 1.8, "Запретные_признания"}};
  shops.push_back(shop2);

  Shop shop3;
  shop3.name = "Свинцовый_дворик";
  shop3.items = {{"Броня", "Гранёная_тюбитейка", 700, 1.2, "60"},
                 {"Оружие", "Резцы_жандарма", 400, 0.1, "50"},
                 {"Оружие", "Зубило_кроманьонца", 300, 0.3, "30"},
                 {"Зелье", "Мондштадт_после_Варки", 200, 2.0, "100.0"},
                 {"Свиток", "Летопись_циничной_устрицы", 600, 0.4,
                  "Чувство_неполноцинности"}};
  shops.push_back(shop3);

  return shops;
}

int main() {
#ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_ALL, "Russian");
#endif

  auto shops = createShopsData();

  for (const auto& shop : shops) {
    double priceSum = 0;
    double weightSum = 0;

    std::vector<Weapon> shopWeapons;
    std::vector<Armor> shopArmors;
    std::vector<Potion> shopPotions;
    std::vector<Scroll> shopScrolls;

    for (const auto& item : shop.items) {
      priceSum += item.price;
      weightSum += item.weight;

      if (item.type == "Оружие") {
        int damage = std::stoi(item.specParam);
        shopWeapons.push_back(
            Weapon(item.name, item.price, item.weight, damage));
      } else if (item.type == "Броня") {
        int defense = std::stoi(item.specParam);
        shopArmors.push_back(
            Armor(item.name, item.price, item.weight, defense));
      } else if (item.type == "Зелье") {
        double duration = std::stod(item.specParam);
        shopPotions.push_back(
            Potion(item.name, item.price, item.weight, duration));
      } else if (item.type == "Свиток") {
        shopScrolls.push_back(
            Scroll(item.name, item.price, item.weight, item.specParam));
      }
    }

    std::cout << "\n=== Магазин: " << shop.name << " ===" << std::endl;
    std::cout << "Всего предметов: " << shop.items.size() << std::endl;
    std::cout << "Средняя цена: " << priceSum / shop.items.size() << std::endl;
    std::cout << "Средний вес: " << weightSum / shop.items.size() << " кг\n";
    std::cout << "\nСтатистика по предметам:" << std::endl;

    if (!shopWeapons.empty()) {
      double damageSum = 0;
      for (const auto& weapon : shopWeapons) {
        auto param = weapon.getSpecParam();
        damageSum += std::get<int>(param);
      }
      std::cout << "- Оружие: средний урон = " << damageSum / shopWeapons.size()
                << std::endl;
    } else {
      std::cout << "- Оружие: нет в наличии" << std::endl;
    }

    if (!shopArmors.empty()) {
      double defenseSum = 0;
      for (const auto& armor : shopArmors) {
        auto param = armor.getSpecParam();
        defenseSum += std::get<int>(param);
      }
      std::cout << "- Броня: средняя защита = "
                << defenseSum / shopArmors.size() << std::endl;
    } else {
      std::cout << "- Броня: нет в наличии" << std::endl;
    }

    if (!shopPotions.empty()) {
      double durationSum = 0;
      for (const auto& potion : shopPotions) {
        auto param = potion.getSpecParam();
        durationSum += std::get<double>(param);
      }
      std::cout << "- Зелья: средняя длительность = "
                << durationSum / shopPotions.size() << std::endl;
    } else {
      std::cout << "- Зелья: нет в наличии" << std::endl;
    }

    if (!shopScrolls.empty()) {
      std::map<std::string, int> effectCount;
      for (const auto& scroll : shopScrolls) {
        auto param = scroll.getSpecParam();
        std::string effect = std::get<std::string>(param);
        effectCount[effect]++;
      }

      std::string mostCommonEffect;
      int maxCount = 0;
      for (const auto& [effect, count] : effectCount) {
        if (count > maxCount) {
          maxCount = count;
          mostCommonEffect = effect;
        }
      }
      std::cout << "- Свитки: самый частый эффект " << mostCommonEffect
                << std::endl;
    } else {
      std::cout << "- Свитки: нет в наличии" << std::endl;
    }
  }

  return 0;
}
