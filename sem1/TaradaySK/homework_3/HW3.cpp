
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum ObjectTypes { AttackWand, SaveArmor, PaperScroll, MagicPotion };

class MagicItem {
 private:
  std::string ItemName;
  int ItemPrice;
  double ItemWeight;
  ObjectTypes Type;

 public:
  MagicItem(ObjectTypes Type, std::string& Name, int Price, double Weight)
      : Type(Type), ItemName(Name), ItemPrice(Price), ItemWeight(Weight) {}
  virtual ~MagicItem() {}
  ObjectTypes GetType() const { return Type; }
  std::string GetName() const { return ItemName; }
  int GetPrice() const { return ItemPrice; }
  double GetWeight() const { return ItemWeight; }
  virtual std::string GetSpecificParametr() const = 0;
};

class Wand : public MagicItem {
 private:
  int SpellPower;

 public:
  Wand(std::string& Name, int Price, double Weight, int Power)
      : MagicItem(AttackWand, Name, Price, Weight), SpellPower(Power) {}
  std::string GetSpecificParametr() const override {
    return std::to_string(SpellPower);
  }
  std::string GetSpellPower() const { return std::to_string(SpellPower); }
};

class Armor : public MagicItem {
 private:
  int ArmorDefense;

 public:
  Armor(std::string& Name, int Price, double Weight, int Defense)
      : MagicItem(SaveArmor, Name, Price, Weight), ArmorDefense(Defense) {}
  std::string GetSpecificParametr() const override {
    return std::to_string(ArmorDefense);
  }
  std::string GetArmorDefense() const { return std::to_string(ArmorDefense); }
};

class Potion : public MagicItem {
 private:
  std::string PotionEffect;

 public:
  Potion(std::string& Name, int Price, double Weight, std::string Effect)
      : MagicItem(MagicPotion, Name, Price, Weight), PotionEffect(Effect) {}
  std::string GetSpecificParametr() const override { return (PotionEffect); }
  std::string GetPotionEffect() const { return PotionEffect; }
};

class Scroll : public MagicItem {
 private:
  std::string ScrollSpell;

 public:
  Scroll(std::string& Name, int Price, double Weight, std::string Spell)
      : MagicItem(PaperScroll, Name, Price, Weight), ScrollSpell(Spell) {}
  std::string GetSpecificParametr() const override { return (ScrollSpell); }
  std::string GetPotionEffect() const { return ScrollSpell; }
};

class Shop {
 public:
  Shop(std::string Name)
      : ShopName(Name),
        ItemCost(0),
        TypesOfSpells(0),
        TypesOfPotions(0),
        ItemsCount(0),
        WeightOfAll(0.0),
        PriceOfAll(0.0),
        DamageOfAll(0.0),
        SaveOfAll(0.0) {}
  void AddItem(std::unique_ptr<MagicItem> Item) {
    ItemsCount++;
    PriceOfAll += Item->GetPrice();
    WeightOfAll += Item->GetWeight();
    switch (Item->GetType()) {
      case (0):
        DamageOfAll += std::stoi(Item->GetSpecificParametr());
        break;
      case (1):
        SaveOfAll += std::stoi(Item->GetSpecificParametr());
        break;
      case (2):
        Spells[Item->GetSpecificParametr()] += 1;
        if (Spells[Item->GetSpecificParametr()] > TypesOfSpells) {
          TypesOfSpells = Spells[Item->GetSpecificParametr()];
          PopularSpells = Item->GetSpecificParametr();
        }
        break;
      case (3):
        Potions[Item->GetSpecificParametr()] += 1;
        if (Potions[Item->GetSpecificParametr()] > TypesOfPotions) {
          TypesOfPotions = Potions[Item->GetSpecificParametr()];
          PopularPotions = Item->GetSpecificParametr();
        }
        break;
      default:
        break;
    }
    Items[Item->GetType()].push_back(std::move(Item));
  };
  void Results() {
    std::cout << "******************************\n";
    std::cout << "Shop - " << ShopName << std::endl;
    std::cout << "******************************\n";
    std::cout << "Items count - " << ItemsCount << std::endl;
    std::cout << "Average price - " << AverageGetPrice() << std::endl;
    std::cout << "Average weight - " << AverageGetWeight() << std::endl;
    std::cout << "******************************\n";
    std::cout << "Average damage - " << GetDamage() << std::endl;
    std::cout << "Average defense - " << GetSave() << std::endl;
    std::cout << "Popular spell - " << GetPopularSpell() << std::endl;
    std::cout << "Popular potion - " << GetPopularPotion() << std::endl;
    if (GetDamage() == 0) {
      std::cout << "No wands\n";
    }
    if (GetSave() == 0.0) {
      std::cout << "No armor\n";
    }
    std::cout << "******************************\n\n";
  };

 private:
  std::string ShopName, PopularSpells, PopularPotions = "";
  std::map<ObjectTypes, std::vector<std::unique_ptr<MagicItem>>> Items;
  std::map<std::string, int> Spells;
  std::map<std::string, int> Potions;
  int ItemCost = 0;
  int TypesOfSpells = 0;
  int TypesOfPotions = 0;
  int ItemsCount = 0;
  double WeightOfAll = 0.0;
  double PriceOfAll = 0.0;
  double DamageOfAll = 0.0;
  double SaveOfAll = 0.0;
  double AverageGetPrice() {
    if (!ItemsCount) {
      return 0;
    }
    return PriceOfAll / ItemsCount;
  }
  double AverageGetWeight() {
    if (!ItemsCount) {
      return 0.0;
    }
    return WeightOfAll / ItemsCount;
  }
  double GetDamage() {
    if (Items[ObjectTypes::AttackWand].size() == 0) {
      return 0;
    }
    return DamageOfAll / Items[ObjectTypes::AttackWand].size();
  }
  double GetSave() {
    if (Items[ObjectTypes::SaveArmor].size() == 0) {
      return 0;
    }
    return SaveOfAll / Items[ObjectTypes::SaveArmor].size();
  }
  std::string GetPopularSpell() {
    if (PopularSpells != "") {
      return PopularSpells;
    } else {
      return "No spels";
    }
  }
  std::string GetPopularPotion() {
    if (PopularPotions != "") {
      return PopularPotions;
    } else {
      return "No potions";
    }
  }
};
std::unique_ptr<MagicItem> ReadLine(std::string Line) {
  std::istringstream Text(Line);
  std::string Type, Name, SpecialPower;
  int Cost;
  double Weight;
  Text >> Type >> Name >> Cost >> Weight >> SpecialPower;

  if (Type == "MagicWand" || Type == "Armor") {
    try {
      int Power = std::stoi(SpecialPower);
      if (Type == "MagicWand")
        return std::make_unique<Wand>(Name, Cost, Weight, Power);
      else
        return std::make_unique<Armor>(Name, Cost, Weight, Power);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error: can not read " << Line << std::endl;
      return nullptr;
    }
  }
  if (Type == "Scroll") {
    return std::make_unique<Scroll>(Name, Cost, Weight, SpecialPower);
  }
  if (Type == "Potion") {
    return std::make_unique<Potion>(Name, Cost, Weight, SpecialPower);
  }
  return nullptr;
}
int main() {
  std::ifstream Text("HW3.txt");
  std::string Line;
  Shop* VisitedShop = nullptr;
  std::vector<Shop*> AllShops;

  while (getline(Text, Line)) {
    if (Line.find("Shop") == 0) {
      VisitedShop = new Shop(Line.substr(5));
      AllShops.push_back(VisitedShop);
    } else if (!Line.empty()) {
      if (VisitedShop == nullptr) {
        std::cerr << "Error: No shop " << Line << std::endl;
        continue;
      }
      auto item = ReadLine(Line);
      if (item) {
        VisitedShop->AddItem(std::move(item));
      } else {
        std::cerr << "Error: Read object " << Line << std::endl;
      }
    }
  }

  for (Shop* shop : AllShops) {
    shop->Results();
    delete shop;
  }

  return 0;
}
