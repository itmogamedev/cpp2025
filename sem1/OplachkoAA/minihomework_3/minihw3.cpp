#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

class MagicItem {
protected:
  std::string name;
  double price;
  double weight;

public:
  MagicItem(const std::string& n, double p, double w) : name(n), price(p), weight(w) {}
  virtual ~MagicItem() {}
  
  virtual std::string getSpecificParameter() const = 0;
  
  std::string getName() const { return name; }
  double getPrice() const { return price; }
  double getWeight() const { return weight; }
};

class MagicWand : public MagicItem {
private:
  int power;

public:
  MagicWand(const std::string& n, double p, double w, int pow) 
    : MagicItem(n, p, w), power(pow) {}
  
  std::string getSpecificParameter() const override {
    return std::to_string(power);
  }
  
  int getPower() const { return power; }
};

class Potion : public MagicItem {
private:
  std::string effect;

public:
  Potion(const std::string& n, double p, double w, const std::string& e) 
    : MagicItem(n, p, w), effect(e) {}
  
  std::string getSpecificParameter() const override {
    return effect;
  }
  
  std::string getEffect() const { return effect; }
};

class Scroll : public MagicItem {
private:
  std::string spellType;

public:
  Scroll(const std::string& n, double p, double w, const std::string& st) 
    : MagicItem(n, p, w), spellType(st) {}
  
  std::string getSpecificParameter() const override {
    return spellType;
  }
  
  std::string getSpellType() const { return spellType; }
};

class MagicShop {
private:
  std::string name;
  std::vector<MagicItem*> items;

public:
  MagicShop(const std::string& n) : name(n) {}
  
  void addItem(MagicItem* item) {
    items.push_back(item);
  }
  
  void analyzeShop() {
    std::cout << "=== Магазин: " << name << " ===" << std::endl;
    
    if (items.empty()) {
      std::cout << "Магазин пуст!" << std::endl << std::endl;
      return;
    }
    
    double totalPrice = 0, totalWeight = 0;
    for (auto item : items) {
      totalPrice += item->getPrice();
      totalWeight += item->getWeight();
    }
    
    std::cout << "Средняя цена: " << totalPrice / items.size() << " золотых" << std::endl;
    std::cout << "Средний вес: " << totalWeight / items.size() << " кг" << std::endl;
    
    analyzeWands();
    analyzePotions();
    analyzeScrolls();
    
    std::cout << std::endl;
  }
  
  void analyzeWands() {
    std::vector<MagicWand*> wands;
    
    for (auto item : items) {
      MagicWand* wand = dynamic_cast<MagicWand*>(item);
      if (wand) {
        wands.push_back(wand);
      }
    }
    
    if (wands.empty()) {
      std::cout << "Магические палочки: нет в магазине" << std::endl;
      return;
    }
    
    double sum = 0;
    for (auto wand : wands) {
      sum += wand->getPower();
    }
    std::cout << "Магические палочки - Средняя мощность: " << sum / wands.size() << std::endl;
  }
  
  void analyzePotions() {
    std::vector<Potion*> potions;
    
    for (auto item : items) {
      Potion* potion = dynamic_cast<Potion*>(item);
      if (potion) {
        potions.push_back(potion);
      }
    }
    
    if (potions.empty()) {
      std::cout << "Зелья: нет в магазине" << std::endl;
      return;
    }
    
    std::map<std::string, int> frequency;
    for (auto potion : potions) {
      std::string effect = potion->getEffect();
      frequency[effect]++;
    }
    
    std::string mostCommon;
    int maxCount = 0;
    for (auto& pair : frequency) {
      if (pair.second > maxCount) {
        maxCount = pair.second;
        mostCommon = pair.first;
      }
    }
    
    std::cout << "Зелья - Самый частый эффект: " << mostCommon << " (встречается " << maxCount << " раз)" << std::endl;
  }
  
  void analyzeScrolls() {
    std::vector<Scroll*> scrolls;
    
    for (auto item : items) {
      Scroll* scroll = dynamic_cast<Scroll*>(item);
      if (scroll) {
        scrolls.push_back(scroll);
      }
    }
    
    if (scrolls.empty()) {
      std::cout << "Свитки: нет в магазине" << std::endl;
      return;
    }
    
    std::map<std::string, int> frequency;
    for (auto scroll : scrolls) {
      std::string spellType = scroll->getSpellType();
      frequency[spellType]++;
    }
    
    std::string mostCommon;
    int maxCount = 0;
    for (auto& pair : frequency) {
      if (pair.second > maxCount) {
        maxCount = pair.second;
        mostCommon = pair.first;
      }
    }
    
    std::cout << "Свитки - Самый частый тип заклинания: " << mostCommon << " (встречается " << maxCount << " раз)" << std::endl;
  }
  
  ~MagicShop() {
    for (auto item : items) {
      delete item;
    }
  }
};

std::vector<MagicShop*> createTestData() {
  std::vector<MagicShop*> shops;
  
  MagicShop* shop1 = new MagicShop("Волшебный уголок");
  shop1->addItem(new MagicWand("Wand of Fire", 150.5, 0.3, 85));
  shop1->addItem(new MagicWand("Wand of Ice", 120.0, 0.25, 90));
  shop1->addItem(new Potion("Health Potion", 50.0, 0.1, "Healing"));
  shop1->addItem(new Scroll("Fireball Scroll", 200.0, 0.05, "Damage"));
  shop1->addItem(new MagicWand("Wand of Lightning", 180.0, 0.35, 88));
  shops.push_back(shop1);
  
  MagicShop* shop2 = new MagicShop("Алхимическая лавка");
  shop2->addItem(new Potion("Mana Potion", 60.0, 0.15, "Mana Restoration"));
  shop2->addItem(new Potion("Strength Potion", 70.0, 0.12, "Buff"));
  shop2->addItem(new Scroll("Teleport Scroll", 250.0, 0.08, "Utility"));
  shop2->addItem(new Scroll("Invisibility Scroll", 300.0, 0.06, "Stealth"));
  shop2->addItem(new Potion("Invisibility Potion", 90.0, 0.18, "Stealth"));
  shops.push_back(shop2);
  
  MagicShop* shop3 = new MagicShop("Магический базар");
  shop3->addItem(new MagicWand("Storm Wand", 220.0, 0.4, 92));
  shop3->addItem(new Scroll("Light Scroll", 150.0, 0.04, "Illumination"));
  shop3->addItem(new MagicWand("Nature Wand", 130.0, 0.28, 82));
  shop3->addItem(new Potion("Poison Antidote", 45.0, 0.09, "Cure"));
  shop3->addItem(new Scroll("Protection Scroll", 180.0, 0.07, "Defense"));
  shop3->addItem(new Potion("Love Potion", 100.0, 0.2, "Charm"));
  shops.push_back(shop3);
  
  return shops;
}

int main() {
  std::cout << std::endl << "Анализ магазинов магических артефактов Аркадии" << std::endl;
  std::cout << "=============================================" << std::endl << std::endl;
  
  std::vector<MagicShop*> shops = createTestData();
  
  for (auto shop : shops) {
    shop->analyzeShop();
  }
  
  for (auto shop : shops) {
    delete shop;
  }
  
  std::cout << "Анализ завершен!" << std::endl << std::endl;
  return 0;
}