#include "MagicItem.h"

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(std::string, int, double, int);
  std::variant<int, double, std::string> getSpecParam() { return damage; };
};
