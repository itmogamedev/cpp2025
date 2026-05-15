#pragma once
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class MagicItem {
 public:
  std::string name;
  double price;
  double weight;

  MagicItem(const std::string& n, double p, double w)
      : name(n), price(p), weight(w) {}

  virtual std::variant<int, double, std::string> getSpecificParameter()
      const = 0;
  virtual std::string getType() const = 0;
  virtual ~MagicItem() = default;
};

class Weapon;
class Runes;
class Potion;
class Armor;
class Clothes;
class Scroll;

struct shopStats {
  std::string name;
  int totalItems = 0;
  double avgPrice = 0.0, avgWeight = 0.0;
  std::map<std::string, double> typeAvgParams;
  std::map<std::string, std::map<std::string, int>> Effects;
};

std::vector<std::unique_ptr<MagicItem>> readShop(std::ifstream& file,
                                                 std::string shopName);
shopStats calculateStats(std::string shopName,
                         const std::vector<std::unique_ptr<MagicItem>>& items);
void printStats(const shopStats& stats);
void processShops();
