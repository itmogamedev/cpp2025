#include "FileReader.h"

#include <fstream>
#include <iostream>

#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

std::vector<Shop> readShops(const std::string& file) {
  std::ifstream in(file);
  std::vector<Shop> res;

  if (!in) {
    std::cerr << "File error\n";
    return res;
  }

  std::string token;
  while (in >> token) {
    if (token != "Shop:") {
      std::string tmp;
      std::getline(in, tmp);
      continue;
    }

    Shop s;
    in >> s.name;

    std::string lbl;
    int cnt;
    in >> lbl >> cnt;

    for (int i = 0; i < cnt; i++) {
      std::string type, name;
      int price;
      double weight;
      std::string spec;

      in >> type >> name >> price >> weight >> spec;

      if (type == "Weapon")
        s.items.push_back(
            std::make_unique<Weapon>(name, price, weight, std::stoi(spec)));
      else if (type == "Armor")
        s.items.push_back(
            std::make_unique<Armor>(name, price, weight, std::stoi(spec)));
      else if (type == "Potion")
        s.items.push_back(
            std::make_unique<Potion>(name, price, weight, std::stod(spec)));
      else if (type == "Scroll")
        s.items.push_back(std::make_unique<Scroll>(name, price, weight, spec));
    }

    res.push_back(std::move(s));
  }
  return res;
}
