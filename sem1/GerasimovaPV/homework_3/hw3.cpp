//
// Created by polsha on 14.11.2025.
//
#include <format>
#include <vector>
#include <memory>
#include <variant>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <map>

#include "iostream"
#include <windows.h>

class MagicItem {
public:
  std::string name;
  int price = 0;
  double weight = 0.0;

  MagicItem(double w) : weight{w} {
  }

  virtual std::string getType() const = 0;

  virtual std::variant<int, double, std::string> getSpecialParam() const = 0;

  MagicItem(std::string &m_name, int m_price, double m_weight) {
    this->name = m_name;
    this->price = m_price;
    this->weight = m_weight;
  }

  virtual ~MagicItem() = default;
};

class Weapon final : public MagicItem {
public:
  int damage = 0;

  std::string getType() const {
    return "Оружие";
  }

  std::variant<int, double, std::string> getSpecialParam() const {
    return damage;
  }

  Weapon(std::string &w_n, int w_p, double w_w, int w_d) : MagicItem(w_n, w_p, w_w) {
    this->damage = w_d;
  }
};

class Armor final : public MagicItem {
public:
  int defense = 0;

  std::string getType() const {
    return "Броня";
  }

  std::variant<int, double, std::string> getSpecialParam() const override {
    return defense;
  }

  Armor(std::string &a_n, int a_p, double a_w, int a_d) : MagicItem(a_n, a_p, a_w) {
    this->defense = a_d;
  }
};

class Potion final : public MagicItem {
public:
  double duration = 0.0;

  std::string getType() const {
    return "Зелье";
  }

  std::variant<int, double, std::string> getSpecialParam() const override {
    return duration;
  }

  Potion(std::string p_n, int p_p, double p_w, double p_d) : MagicItem(p_n, p_p, p_w) {
    this->duration = p_d;
  }
};

class Scroll final : public MagicItem {
public:
  std::string effect;

  std::string getType() const {
    return "Свиток";
  }

  std::variant<int, double, std::string> getSpecialParam() const override {
    return effect;
  }


  Scroll(std::string s_n, int s_p, double s_w, std::string s_f) : MagicItem(s_n, s_p, s_w) {
    this->effect = s_f;
  }
};

class Shop {
public:
  std::string name;
  int item_sum = 0;
  std::vector<std::unique_ptr<MagicItem> > items;
  double average_price = 0.0;
  double average_weight = 0.0;
};


void addItems(std::ifstream &ifs) {
  Shop shop;
  std::string line;
  std::string trash;
  double average_price = 0.0;
  double average_weight = 0.0;
  std::getline(ifs, line);
  std::istringstream ss(line);
  ss >> trash >> shop.name;
  std::getline(ifs, line);
  ss = std::istringstream{line};
  ss >> trash >> shop.item_sum;
  for (int i = 0; i < shop.item_sum; i++) {
    std::string type;
    std::string name;
    int price = 0;
    double weight = 0.0;
    std::string special_param;
    std::getline(ifs, line);
    ss = std::istringstream{line};
    ss >> type >> name >> price >> weight >> special_param;
    if (type == "Свиток") {
      shop.items.push_back(std::make_unique<Scroll>(name, price, weight, special_param));
    }
    if (type == "Оружие") {
      shop.items.push_back(std::make_unique<Weapon>(name, price, weight, std::stoi(special_param)));
    }
    if (type == "Броня") {
      shop.items.push_back(std::make_unique<Armor>(name, price, weight, std::stoi(special_param)));
    }
    if (type == "Зелье") {
      shop.items.push_back(std::make_unique<Potion>(name, price, weight, std::stod(special_param)));
    }
  }
  double price_sum = 0.0;
  double weight_sum = 0.0;
  int w_s = 0;
  int w = 0;
  int a_s = 0;
  int a = 0;
  double p_s = 0.0;
  int p = 0;
  std::string s_s;
  std::map<std::string, int> special;
  int max = 0;
  std::string key;
  for (auto &num: shop.items) {
    price_sum += num->price;
    weight_sum += num->weight;
    if (num->getType() == "Оружие") {
      w_s += std::get<int>(num->getSpecialParam());
      w += 1;
    }
    if (num->getType() == "Броня") {
      a_s += std::get<int>(num->getSpecialParam());
      a += 1;
    }
    if (num->getType() == "Зелье") {
      p_s += std::get<double>(num->getSpecialParam());
      p += 1;
    }
    if (num->getType() == "Свиток") {
      std::string k = std::get<std::string>(num->getSpecialParam());
      special[k] += 1;
      if (special[k] > max) {
        key = k;
        max = special[k];
      }
    }
  }
  std::cout << "Магазин: " << std::format("{}", shop.name) << std::endl;
  std::cout << "Всего предметов: " << std::format("{}", shop.item_sum) << std::endl;
  std::cout << "Среднияя цена: " << price_sum / shop.items.size() << " золота" << std::endl;
  std::cout << "Средний вес: " << weight_sum / shop.items.size() << " кг" << std::endl;
  std::cout << std::endl << "Статистика по предметам:" << std::endl;
  if (w != 0) {
    std::cout << "- Оружие: средний урон = " << w_s / w << std::endl;
  } else {
    std::cout << "- Оружие: нет в наличии" << std::endl;
  }
  if (a != 0) {
    std::cout << "- Броня: средняя защита = " << a_s / a << std::endl;
  } else {
    std::cout << "- Броня: нет в наличии" << std::endl;
  }
  if (p != 0) {
    std::cout << "- Зелья: средняя длительность = " << p_s / p << std::endl;
  } else {
    std::cout << "- Зелья: нет в наличии" << std::endl;
  }
  if (max != 0) {
    std::cout << "- Свитки: самый частый эффект = " << key << std::endl << std::endl;
  } else {
    std::cout << "- Свитки: нет в наличии" << std::endl << std::endl;
  }
  std::getline(ifs, line);
}


int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
  std::ifstream ifs("./Shop.txt");
  while (!ifs.eof()) {
    addItems(ifs);
  }
}
