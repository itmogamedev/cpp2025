#include "functions.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

void readFile(std::string filename) {
  std::ifstream fin;
  std::string line;
  fin.open(filename);
  if (!fin.is_open()) {
    std::cout << "ошибка при открытии файла" << std::endl;
  } else {
    std::vector<MagicItem*> items;
    while (std::getline(fin, line)) {
      std::istringstream iss(line);
      std::string first_word;
      iss >> first_word;

      if (first_word == "Магазин:") {
        std::string second_word;
        iss >> second_word;
        std::cout << "=== Магазин: " << second_word << " ===" << std::endl;
      } else if (first_word == "Предметы:") {
        std::string second_word;
        iss >> second_word;
        std::cout << "Всего предметов: " << second_word << std::endl;
      } else if (first_word == "Оружие") {
        Weapon* weapon = new Weapon(line);
        items.push_back(weapon);
      } else if (first_word == "Броня") {
        Armor* armor = new Armor(line);
        items.push_back(armor);
      } else if (first_word == "Зелье") {
        Potion* potion = new Potion(line);
        items.push_back(potion);
      } else if (first_word == "Свиток") {
        Scroll* scroll = new Scroll(line);
        items.push_back(scroll);
      } else if (first_word == "---") {
        std::cout << "Средняя цена: " << averangeCost(items) << " золота"
                  << std::endl;
        std::cout << "Средний вес: " << averangeWeight(items) << " кг"
                  << std::endl;
        std::cout << "========= Подробная статистика =========" << std::endl;
        std::cout << "Оружие: " << averangeAtack(items) << std::endl;
        std::cout << "Броня: " << averangeDefense(items) << std::endl;
        std::cout << "Зелья: " << averangeDuration(items) << std::endl;
        std::cout << "Свитки: " << mostCommonEfect(items) << std::endl;
        std::cout << std::endl;

        for (auto* item : items) {
          delete item;
        }
        items.clear();
      }
    }
    fin.close();
  }
}

std::string averangeCost(std::vector<MagicItem*> items) {
  int common_cost = 0;
  int count_of_items = 0;
  while (count_of_items < items.size()) {
    common_cost += items[count_of_items]->getPrice();
    count_of_items += 1;
  }
  if (count_of_items == 0) return "бесценно:)";

  double average = static_cast<double>(common_cost) / count_of_items;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << average;
  return ss.str();
}

std::string averangeWeight(std::vector<MagicItem*> items) {
  double common_weight = 0;
  int count_of_items = 0;
  while (count_of_items < items.size()) {
    common_weight += items[count_of_items]->getWeight();
    count_of_items += 1;
  }
  if (count_of_items == 0) return "нет веса видимо";

  double average = common_weight / count_of_items;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << average;
  return ss.str();
}

std::string averangeAtack(std::vector<MagicItem*> items) {
  int common_atack = 0;
  int count_of_items = 0;
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->getType() == "Оружие") {
      count_of_items += 1;
      SpecialParam param = items[i]->getSpecParam();
      if (std::holds_alternative<int>(param)) {
        common_atack += std::get<int>(param);
      }
    }
  }
  if (count_of_items == 0) {
    return "нет в наличии";
  }

  double average = static_cast<double>(common_atack) / count_of_items;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1) << average;
  return "средний урон: " + ss.str();
}

std::string averangeDefense(std::vector<MagicItem*> items) {
  int common_defence = 0;
  int count_of_items = 0;
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->getType() == "Броня") {
      count_of_items += 1;
      SpecialParam param = items[i]->getSpecParam();
      if (std::holds_alternative<int>(param)) {
        common_defence += std::get<int>(param);
      }
    }
  }
  if (count_of_items == 0) {
    return "нет в наличии";
  }

  double average = static_cast<double>(common_defence) / count_of_items;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1) << average;
  return "средняя защита: " + ss.str();
}

std::string averangeDuration(std::vector<MagicItem*> items) {
  double common_duration = 0.0;
  int count_of_items = 0;
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->getType() == "Зелье") {
      count_of_items += 1;
      SpecialParam param = items[i]->getSpecParam();
      if (std::holds_alternative<double>(param)) {
        common_duration += std::get<double>(param);
      }
    }
  }
  if (count_of_items == 0) {
    return "нет в наличии";
  }

  double average = common_duration / count_of_items;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1) << average;
  return "средняя длительность: " + ss.str();
}

std::string mostCommonEfect(std::vector<MagicItem*> items) {
  std::vector<std::string> efects;
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->getType() == "Свиток") {
      SpecialParam param = items[i]->getSpecParam();
      if (std::holds_alternative<std::string>(param)) {
        efects.push_back(std::get<std::string>(param));
      }
    }
  }
  if (efects.size() == 0) {
    return "Свитков нет в наличии, идите в Винтерхолд";
  }
  std::map<std::string, int> frequency;
  for (int i = 0; i < efects.size(); i++) {
    frequency[efects[i]]++;
  }
  std::string most_common;
  int max_count = 0;
  for (std::pair<std::string, int> pair : frequency) {
    if (pair.second > max_count) {
      max_count = pair.second;
      most_common = pair.first;
    }
  }

  if (max_count == 1) {
    return "нет преобладающих свитков, всех по одному, например: " +
           most_common;
  } else {
    return "самый частый эффект: " + most_common + " (встречается " +
           std::to_string(max_count) + " раз)";
  }
}
