//объявление базового класса и его функций
#pragma once

#include <iostream>
#include <string>

class MagicItem {  // объявление абстрактного класса MagicItem
 public:
  MagicItem(std::string name, int price,
            double weight);        // конструктор MagicItem
  virtual ~MagicItem() = default;

  const std::string& getName() const;
  int getPrice() const;
  double getWeight() const;

  virtual void printSpecParam(std::ostream& os) const = 0;  //функция вывода специфического параметра
  virtual const char* getTypeName() const = 0;              //функция возвращения типа предмета

 protected:
  std::string name;
  int price;
  double weight;
};