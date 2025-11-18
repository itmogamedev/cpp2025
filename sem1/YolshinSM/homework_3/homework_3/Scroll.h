#include "MagicItem.h"
class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(std::string, int, double, std::string);
  std::variant<int, double, std::string> getSpecParam() { return effect; };
};
