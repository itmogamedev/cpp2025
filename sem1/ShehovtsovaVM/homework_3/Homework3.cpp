#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Item.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <algorithm>


std::string variant_to_string(const std::variant<int, double, std::string>& var,
                              int precision = 6) {
  return std::visit(
      [precision](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
          return std::to_string(arg);
        } else if constexpr (std::is_same_v<T, double>) {
          std::stringstream ss;
          ss << std::fixed << std::setprecision(precision) << arg;
          return ss.str();
        } else if constexpr (std::is_same_v<T, std::string>) {
          return arg;
        }
      },
      var);
}
int variant_to_int(const std::variant<int, double, std::string>& var) {
  return std::visit(
      [](auto&& arg) -> int {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
          return arg;
        } else if constexpr (std::is_same_v<T, double>) {
          return static_cast<int>(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
          try {
            return std::stoi(arg);
          } catch (const std::exception&) {
            throw std::invalid_argument("Cannot convert string to integer");
          }
        }
      },
      var);
}
double variant_to_double(const std::variant<int, double, std::string>& var) {
  return std::visit(
      [](auto&& arg) -> double {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
          return static_cast<double>(arg);
        } else if constexpr (std::is_same_v<T, double>) {
          return arg;
        } else if constexpr (std::is_same_v<T, std::string>) {
          try {
            return std::stod(arg);
          } catch (const std::exception&) {
            throw std::invalid_argument("Cannot convert string to double");
          }
        }
      },
      var);
}

int main() { 
  setlocale(LC_ALL, "Russian");
  std::string line;
  std::ifstream in("Text.txt");  
  std::vector<Weapon> weapons;
  std::vector<Armor> armory;
  std::vector<Potion> potions;
  std::vector<Scroll> scrolls;
  int shop_num, items_num, sum_damage = 0, sum_defense = 0;
  int sum_price = 0;
  double sum_weight = 0, sum_duration = 0;
  std::string shop_name, type, most_popular_effect;
  std::string name;
 // std::variant<int, double, std::string> sum;
  int price;
  double weight;
  if (in.is_open()) {
    in >> shop_num;
    for (int i = 0; i < shop_num; i++) {
      in >> shop_name >> items_num;
      for (int j = 0; j < items_num; j++) {
        in >> type >> name >> price >> weight;
        if (type == "w") {
          int buf;
          in >> buf;
          Weapon w = Weapon(name,price,weight,buf);
          weapons.push_back(w);
        } 
        else if (type == "a") {
          int buf;
          in >> buf;
          Armor a = Armor(name, price, weight, buf);
          armory.push_back(a);
        } 
        else if (type == "p") {
          double buf;
          in >> buf;
          Potion p = Potion(name, price, weight, buf);
          potions.push_back(p);
        } 
        else {
          std::string buf;
          in >> buf;
          Scroll s = Scroll(name, price, weight, buf);
          scrolls.push_back(s);
        }
      }
      //счет ср знача
       for (Weapon i : weapons) {
        sum_price += i.getPrice();
        sum_weight += i.getWeight();
        sum_damage += std::get<int>(i.getSpecParam());
      }
       for (Armor i : armory) {
        sum_price += i.getPrice();
        sum_weight += i.getWeight();
        sum_defense += std::get<int>(i.getSpecParam());
      }
      for (Potion i : potions) {
        sum_price += i.getPrice();
        sum_weight += i.getWeight();
        sum_duration += std::get<double>(i.getSpecParam());
      }
      std::vector<std::string> effects;
      std::vector<int> effect_counter;
      for (Scroll i : scrolls) {
        sum_price += i.getPrice();
        sum_weight += i.getWeight();
        if (std::find(effects.begin(), effects.end(),
                      std::get<std::string>(i.getSpecParam())) != effects.end()) {
          effect_counter[std::distance(
              effects.begin(),
              std::find(effects.begin(), effects.end(),
                        std::get<std::string>(i.getSpecParam())))] += 1;
        } 
        else {
          effects.push_back(std::get<std::string>(i.getSpecParam()));
          effect_counter.push_back(1);
        }
      }
      most_popular_effect = effects[std::distance(
          effect_counter.begin(), std::find(effect_counter.begin(), effect_counter.end(),
                    *std::min_element(effect_counter.begin(), effect_counter.end())))];
       // std::distance(effect_counter.begin(), effect_counter.end(), std::find(effect_counter.begin(), effects.end(),1));
      //вывод
      std::cout << shop_name
                << "\n";
      std::cout << "Всего предметов: " << items_num << "\n";
      std::cout << "Средняя цена: " << sum_price / items_num << '\n';
      std::cout << "Средний вес: " << sum_weight / items_num << '\n';
      std::cout << "Статистика по предметам:"  << '\n';
      if (weapons.size() > 0) {
        std::cout << "Оружие: средний урон " << sum_damage/weapons.size()<< '\n';
      } else {
        std::cout << "Оружие: нет в наличии\n";
      }
      if (armory.size() > 0) {
        std::cout << "Броня: средняя защита " << sum_defense/armory.size()<< '\n';
      } else {
        std::cout << "Броня: нет в наличии\n";
      }
      if (potions.size() > 0) {
        std::cout << "Зелья: средняя длительность " << sum_duration/potions.size() << '\n';
      } else {
        std::cout << "Зелья: нет в наличии\n";
      }
      if (scrolls.size() > 1 || (i==0 && scrolls.size()>0)) {
        std::cout << "Свитки: самый частый эффект " << most_popular_effect << '\n';
      } else {
        std::cout << "Свитки: нет в наличии\n";
      }
      std::cout << '\n';
      //тгддшанштп
      sum_damage = 0;
      sum_defense = 0;
      sum_price = 0;
      sum_weight = 0;
      sum_duration = 0;
      int s = weapons.size();
      for (int i = 0; i < s; i++) {
        weapons.pop_back();
      }
      s = armory.size();
      for (int i = 0; i < s; i++) {
        armory.pop_back();
      }
      s = potions.size();
      for (int i = 0; i < s; i++) {
        potions.pop_back();
      }
      s = scrolls.size();
      //std::cout << "AAAAAAAAAAAAA" << s;
      /* for (int i = 0; i < s - 1; i++) {
        scrolls.erase(scrolls.begin() + i);
      }
      scrolls[0] = Scroll("", 0, 0, "");*/
      /* weapons.clear();
      armory.clear();
      potions.clear();
      scrolls.clear();*/
    }
  }
  in.close();
}

