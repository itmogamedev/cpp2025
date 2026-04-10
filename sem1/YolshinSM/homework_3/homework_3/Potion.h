#include "MagicItem.h"
class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(std::string, int, double, double);
  std::variant<int, double, std::string> getSpecParam() { return duration; };
};
