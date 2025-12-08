#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

// Type for special parameter
using SpecialParam = std::variant<int, double, std::string>;

// Abstract base class
class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& name, int price, double weight)
      : name(name), price(price), weight(weight) {}

  virtual ~MagicItem() = default;

  // Pure virtual method for getting special parameter
  virtual SpecialParam getSpecParam() const = 0;

  // Virtual method for getting item type
  virtual std::string getType() const = 0;

  // Getters
  std::string getName() const { return name; }
  int getPrice() const { return price; }
  double getWeight() const { return weight; }
};

// Weapon class
class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& name, int price, double weight, int damage)
      : MagicItem(name, price, weight), damage(damage) {}

  SpecialParam getSpecParam() const override { return damage; }

  std::string getType() const override { return "Weapon"; }
};

// Armor class
class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(const std::string& name, int price, double weight, int defense)
      : MagicItem(name, price, weight), defense(defense) {}

  SpecialParam getSpecParam() const override { return defense; }

  std::string getType() const override { return "Armor"; }
};

// Potion class
class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& name, int price, double weight, double duration)
      : MagicItem(name, price, weight), duration(duration) {}

  SpecialParam getSpecParam() const override { return duration; }

  std::string getType() const override { return "Potion"; }
};

// Scroll class
class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& name, int price, double weight,
         const std::string& effect)
      : MagicItem(name, price, weight), effect(effect) {}

  SpecialParam getSpecParam() const override { return effect; }

  std::string getType() const override { return "Scroll"; }
};

// Class to represent a shop
class Shop {
 private:
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;

 public:
  Shop(const std::string& name) : name(name) {}

  void addItem(std::unique_ptr<MagicItem> item) {
    items.push_back(std::move(item));
  }

  // Shop analysis
  void analyze() const {
    std::cout << "=== Shop: " << name << " ===" << std::endl;
    std::cout << "Total items: " << items.size() << std::endl;

    // Average price and weight
    double totalPrice = 0;
    double totalWeight = 0;

    for (const auto& item : items) {
      totalPrice += item->getPrice();
      totalWeight += item->getWeight();
    }

    double avgPrice = items.empty() ? 0 : totalPrice / items.size();
    double avgWeight = items.empty() ? 0 : totalWeight / items.size();

    std::cout << "Average price: " << std::fixed << std::setprecision(2)
              << avgPrice << " gold" << std::endl;
    std::cout << "Average weight: " << std::fixed << std::setprecision(2)
              << avgWeight << " kg" << std::endl;

    std::cout << "\nStatistics by item type:" << std::endl;

    // Statistics by item types
    analyzeByType("Weapon");
    analyzeByType("Armor");
    analyzeByType("Potion");
    analyzeByType("Scroll");

    std::cout << std::endl;
  }

 private:
  void analyzeByType(const std::string& type) const {
    std::vector<SpecialParam> params;

    // Collect special parameters for this type
    for (const auto& item : items) {
      if (item->getType() == type) {
        params.push_back(item->getSpecParam());
      }
    }

    if (params.empty()) {
      std::cout << "- " << type << ": not available" << std::endl;
      return;
    }

    // Calculate average value based on data type
    if (type == "Weapon" || type == "Armor") {
      // For int parameters (damage, defense)
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<int>(param);
      }
      double avg = sum / params.size();
      std::cout << "- " << type << ": average "
                << (type == "Weapon" ? "damage" : "defense") << " = "
                << static_cast<int>(avg) << std::endl;
    } else if (type == "Potion") {
      // For double parameters (duration)
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<double>(param);
      }
      double avg = sum / params.size();
      std::cout << "- " << type << ": average duration = " << std::fixed
                << std::setprecision(1) << avg << std::endl;
    } else if (type == "Scroll") {
      // For string parameters (effect) - find most frequent
      std::map<std::string, int> frequency;
      for (const auto& param : params) {
        frequency[std::get<std::string>(param)]++;
      }

      std::string mostCommon;
      int maxCount = 0;
      for (const auto& [effect, count] : frequency) {
        if (count > maxCount) {
          maxCount = count;
          mostCommon = effect;
        }
      }

      std::cout << "- " << type << ": most common effect is " << mostCommon
                << std::endl;
    }
  }
};

// Function to read data from file
std::vector<Shop> readShopsFromFile(const std::string& filename) {
  std::vector<Shop> shops;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    return shops;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("Shop:") == 0) {
      // Read shop name
      std::string shopName = line.substr(6);  // Skip "Shop: "

      // Read number of items
      std::getline(file, line);
      if (line.find("Items:") == 0) {
        int itemCount = std::stoi(line.substr(7));  // Skip "Items: "

        Shop shop(shopName);

        // Read items
        for (int i = 0; i < itemCount && std::getline(file, line); ++i) {
          std::istringstream iss(line);
          std::string type, name;
          int price;
          double weight;

          iss >> type >> name >> price >> weight;

          if (type == "Weapon") {
            int damage;
            iss >> damage;
            shop.addItem(std::make_unique<Weapon>(name, price, weight, damage));
          } else if (type == "Armor") {
            int defense;
            iss >> defense;
            shop.addItem(std::make_unique<Armor>(name, price, weight, defense));
          } else if (type == "Potion") {
            double duration;
            iss >> duration;
            shop.addItem(
                std::make_unique<Potion>(name, price, weight, duration));
          } else if (type == "Scroll") {
            std::string effect;
            iss >> effect;
            shop.addItem(std::make_unique<Scroll>(name, price, weight, effect));
          }
        }

        shops.push_back(std::move(shop));
      }
    }
  }

  file.close();
  return shops;
}

// Function to create test data file
void createTestFile() {
  std::ofstream file("magic_shops.txt");

  file << "Shop: Gun_Shop\n";
  file << "Items: 5\n";
  file << "Weapon Void_Shotgun 499 3.5 85\n";
  file << "Armor Gunknight_Helmet 799 5.2 60\n";
  file << "Potion Healing_Water 299 0.1 50.0\n";
  file << "Weapon JK-47 199 4.8 95\n";
  file << "Armor Gunknight_Gauntlet 600 2.1 45\n";
  file << "\n";

  file << "Shop: Bazaar_Between_Time\n";
  file << "Items: 6\n";
  file << "Weapon Visions_Of_Heresy 1000 2.1 70\n";
  file << "Scroll Transcendence 300 0.4 Transform_all_health_into_shield\n";
  file << "Potion Spinel_Tonic 250 0.2 20.0\n";
  file << "Scroll Transcendence 300 0.4 Transform_all_health_into_shield\n";
  file << "Scroll Glowing_Meteorite 600 0.5 Meteorfall\n";
  file << "Weapon Hooks_Of_Heresy 900 1.2 55\n";
  file << "\n";

  file << "Shop: Store_Of_Elden\n";
  file << "Items: 5\n";
  file << "Potion Ironjar_Aromatic 400 0.3 25.0\n";
  file << "Potion Acid_Spraymist 350 0.2 20.0\n";
  file << "Potion Uplifting_Aromatic 500 1.5 100.0\n";
  file << "Scroll Star_Shower 300 0.3 StarShower\n";
  file << "Weapon Rivers_Of_Blood 2000 2.0 50\n";

  file.close();
}

int main() {
  // Create test file
  createTestFile();
  std::cout << "Test file 'magic_shops.txt' created successfully!\n\n";

  // Read data from file
  std::vector<Shop> shops = readShopsFromFile("magic_shops.txt");

  if (shops.empty()) {
    std::cerr << "Failed to load shop data." << std::endl;
    return 1;
  }

  // Analyze each shop
  for (const auto& shop : shops) {
    shop.analyze();
  }

  return 0;
}
