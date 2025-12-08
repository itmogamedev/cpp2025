#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "MagicItem.h"

std::vector<std::string> seporate_words;
std::vector<std::string> splitToWords(std::string str);
double midSpecial(std::vector<Weapon> v);
double midSpecial(std::vector<Armor> v);
double midSpecial(std::vector<Posion> v);
std::string midSpecial(std::vector<Scroll> v);
void writeOut();
int main() { writeOut(); }
std::vector<std::string> splitToWords(std::string str) {
  std::vector<std::string> words;
  int start, end;
  start = end = 0;
  while ((start = str.find_first_not_of(' ', end)) != std::string::npos) {
    end = str.find(' ', start);
    words.push_back(str.substr(start, end - start));
  }
  return words;
}
double midSpecial(std::vector<Weapon> v) {
  if (v.empty()) {
    return 0;
  }
  double res{0};
  for (Weapon i : v) {
    res += std::stod(i.getSpecialParm());
  }
  return res / v.size();
}
double midSpecial(std::vector<Armor> v) {
  if (v.empty()) {
    return 0;
  }
  double res{0};
  for (Armor i : v) {
    res += std::stod(i.getSpecialParm());
  }
  return res / v.size();
}
double midSpecial(std::vector<Posion> v) {
  if (v.empty()) {
    return 0;
  }
  double res{0};
  for (Posion i : v) {
    res += std::stod(i.getSpecialParm());
  }
  return res / v.size();
}
std::string midSpecial(std::vector<Scroll> v) {
  if (v.empty()) {
    return "";
  }
  std::string res;
  std::vector<std::string> words;
  for (Scroll i : v) {
    words.push_back(i.getSpecialParm());
  }
  int count{0};
  int max_count{0};
  for (std::string i : words) {
    count = 0;
    for (std::string j : words) {
      if (i == j) {
        count++;
      }
    }
    if (count > max_count) {
      max_count = count;
      res = i;
    }
  }
  return res;
}
void asorimentOut(int costs, int items_count,
                  std::vector<Weapon>& weapons_in_shop,
                  std::vector<Armor>& armors_in_shop,
                  std::vector<Posion>& posions_in_shop,
                  std::vector<Scroll>& scrolls_in_shop) {
  std::cout << "Mid cost: " << costs / items_count << std::endl;
  if (weapons_in_shop.empty()) {
    std::cout << "wepons out of stock" << std::endl;
  } else {
    std::cout << "mid damage " << midSpecial(weapons_in_shop) << std::endl;
  }
  if (armors_in_shop.empty()) {
    std::cout << "armors out of stock " << std::endl;
  } else {
    std::cout << "mid defence " << midSpecial(armors_in_shop) << std::endl;
  }
  if (posions_in_shop.empty()) {
    std::cout << "posions out of stock " << std::endl;
  } else {
    std::cout << "mid duration " << midSpecial(posions_in_shop) << std::endl;
  }
  if (scrolls_in_shop.empty()) {
    std::cout << "seporate out of stock" << std::endl;
  } else {
    std::cout << "mid effect " << midSpecial(scrolls_in_shop) << std::endl;
  }
}
void writeOut() {
  std::string line;
  std::ifstream file;

  file.open("Shops.txt", std::ios::in);
  if (file.is_open()) {
    std::string word;
    int costs{0};
    int items_count{10};
    int temp{0};
    std::vector<Weapon> weapons_in_shop;
    std::vector<Armor> armors_in_shop;
    std::vector<Posion> posions_in_shop;
    std::vector<Scroll> scrolls_in_shop;
    while (std::getline(file, line)) {
      seporate_words = splitToWords(line);
      if (seporate_words[0] == "Shop:") {
        std::cout << "=== Shop - " << seporate_words[1] << " ===" << std::endl;
        weapons_in_shop = {};
        armors_in_shop = {};
        posions_in_shop = {};
        scrolls_in_shop = {};
        costs = 0;

      } else if (seporate_words[0] == "Item_Count:") {
        std::cout << "Item count: " << seporate_words[1] << std::endl;
        items_count = std::stoi(seporate_words[1]);
        temp = 0;

      } else if (seporate_words[0] == "Weapon") {
        weapons_in_shop.push_back(
            Weapon(seporate_words[1], std::stoi(seporate_words[2]),
                   std::stoi(seporate_words[3]), std::stoi(seporate_words[4])));
        costs += std::stoi(seporate_words[2]);
        temp++;
      } else if (seporate_words[0] == "Armor") {
        armors_in_shop.push_back(
            Armor(seporate_words[1], std::stoi(seporate_words[2]),
                  std::stoi(seporate_words[3]), std::stoi(seporate_words[4])));
        costs += std::stoi(seporate_words[2]);
        temp++;
      } else if (seporate_words[0] == "Posion") {
        posions_in_shop.push_back(
            Posion(seporate_words[1], std::stoi(seporate_words[2]),
                   std::stoi(seporate_words[3]), std::stod(seporate_words[4])));
        costs += std::stoi(seporate_words[2]);
        temp++;
      } else if (seporate_words[0] == "Scroll") {
        scrolls_in_shop.push_back(
            Scroll(seporate_words[1], std::stoi(seporate_words[2]),
                   std::stoi(seporate_words[3]), seporate_words[4]));
        costs += std::stoi(seporate_words[2]);
        temp++;
      }
      if (temp >= items_count) {
        asorimentOut(costs, items_count, weapons_in_shop, armors_in_shop,
                     posions_in_shop, scrolls_in_shop);
        temp = 0;
      }
    }

  } else {
    std::cout << "Error with file opening";
  }
  file.close();
}
