#ifndef STORE_H_
#define STORE_H_

#include "MagicItem.h"

#include <vector>
#include <string>

class Store {
 public:
  Store(std::string name)
    : name(name) {}
  
  bool AddItem(MagicItem* mi);

  std::string PrintStatistics();

  ~Store();

 private:
  std::string             name;
  std::vector<MagicItem*> items;
};

#endif // STORE_H_
