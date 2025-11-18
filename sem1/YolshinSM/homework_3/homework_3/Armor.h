#include "MagicItem.h"
class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(std::string, int, double, int);
  std::variant<int, double, std::string> getSpecParam() { return defense; };
};
