#include <format>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <vector>
#include <windows.h>

class MagicItem
{
protected:
  std::string name;
  int price = 0;
  double weight = 0;

public:
  const std::string& getName() const
  {
    return name;
  }

  int getPrice() const
  {
    return price;
  }

  double getWeight() const
  {
    return weight;
  }

  virtual std::string getSpecialParam() const = 0;
  virtual std::string getTypeName() const = 0;

  virtual ~MagicItem()
  {
  }
};

class Weapon final : public MagicItem
{
public:
  int damage = 0;

  std::string getSpecialParam() const override
  {
    return std::format("{0}", damage);
  }

  std::string getTypeName() const override
  {
    return "Оружие";
  }

  Weapon(const std::string& w_name, const int w_price, const double w_weight, const int w_damage)
  {
    this->name = w_name;
    this->price = w_price;
    this->weight = w_weight;
    this->damage = w_damage;
  }

  ~Weapon() override
  {
  }
};

class Armor final : public MagicItem
{
public:
  int defense = 0;

  std::string getSpecialParam() const override
  {
    return std::format("{0}", defense);
  }

  std::string getTypeName() const override
  {
    return "Броня";
  }

  Armor(const std::string& a_name, const int a_price, const double a_weight, const int a_defense)
  {
    this->name = a_name;
    this->price = a_price;
    this->weight = a_weight;
    this->defense = a_defense;
  }

  ~Armor() override
  {
  }
};

class Potion final : public MagicItem
{
public:
  double duration = 0;

  std::string getSpecialParam() const override
  {
    return std::format("{0}", duration);
  }

  std::string getTypeName() const override
  {
    return "Зелье";
  }

  Potion(const std::string& p_name, const int p_price, const double p_weight, const double p_duration)
  {
    this->name = p_name;
    this->price = p_price;
    this->weight = p_weight;
    this->duration = p_duration;
  }

  ~Potion() override
  {
  }
};

class Scroll final : public MagicItem
{
public:
  std::string effect;

  std::string getSpecialParam() const override
  {
    return effect;
  }

  std::string getTypeName() const override
  {
    return "Свиток";
  }

  Scroll(const std::string& s_name, const int s_price, const double s_weight, const std::string& s_effect)
  {
    this->name = s_name;
    this->price = s_price;
    this->weight = s_weight;
    this->effect = s_effect;
  }

  ~Scroll() override
  {
  }
};

constexpr unsigned int hash(const std::string& str, const int h = 0)
{
  return !str[h] ? 55 : hash(str, h + 1) * 33 ^ str[h];
}

std::unique_ptr<MagicItem> parseItem(std::istringstream& line)
{
  std::string ty, name;
  int price;
  double weight;

  line >> ty >> name >> price >> weight;

  switch (hash(ty))
  {
  case hash("Оружие"):
    {
      int damage;
      line >> damage;
      return std::make_unique<Weapon>(name, price, weight, damage);
    }
  case hash("Броня"):
    {
      int defense;
      line >> defense;
      return std::make_unique<Armor>(name, price, weight, defense);
    }
  case hash("Зелье"):
    {
      double duration;
      line >> duration;
      return std::make_unique<Potion>(name, price, weight, duration);
    }
  case hash("Свиток"):
    {
      std::string effect;
      line >> effect;
      return std::make_unique<Scroll>(name, price, weight, effect);
    }
  default:
    break;
  }
  return std::make_unique<Weapon>(name, 0, 0, 0);
}

class Shop
{
  std::vector<std::unique_ptr<MagicItem>> items;

public:
  void addItem(std::unique_ptr<MagicItem> item)
  {
    items.push_back(std::move(item));
  }

  double getAveragePrice() const
  {
    if (items.empty()) return 0.0;
    double total = 0;
    for (const auto& item : items)
    {
      total += item->getPrice();
    }
    return total / items.size();
  }

  double getAverageWeight() const
  {
    if (items.empty()) return 0.0;
    double total = 0.0;
    for (const auto& item : items)
    {
      total += item->getWeight();
    }
    return total / items.size();
  }

  void analyzeSpecialParams() const
  {
    std::map<std::string, std::vector<std::string>> typeParams;

    for (const auto& item : items)
    {
      typeParams[item->getTypeName()].push_back(item->getSpecialParam());
    }

    const std::vector<std::string> allTypes = {"Оружие", "Броня", "Зелье", "Свиток"};

    std::cout << "Статистика по предметам:" << std::endl;
    for (const auto& type : allTypes)
    {
      std::cout << "- " << type << ": ";

      if (!typeParams.contains(type))
      {
        std::cout << "нет в наличии" << std::endl;
        continue;
      }

      const auto& params = typeParams[type];

      if (type == "Оружие" || type == "Броня" || type == "Зелье")
      {
        double sum = 0.0;
        for (const auto& param : params)
        {
          sum += stoi(param);
        }
        switch (hash(type))
        {
        case hash("Оружие"):
          std::cout << std::format("средний урон = {:.2f} ", sum / params.size()) << std::endl;
          break;
        case hash("Броня"):
          std::cout << std::format("средняя защита = {:.2f} ", sum / params.size()) << std::endl;
          break;
        case hash("Зелье"):
          std::cout << std::format("средняя длительность = {:.2f} ", sum / params.size()) << std::endl;
          break;
        default:
          break;
        }
      }
      else if (type == "Свиток")
      {
        std::map<std::string, int> effectCount;
        for (const auto& effect : params)
        {
          effectCount[effect]++;
        }

        std::string mostCommon;
        int maxCount = 0;
        for (const auto& [effect, count] : effectCount)
        {
          if (count > maxCount)
          {
            maxCount = count;
            mostCommon = effect;
          }
        }
        std::cout << "самый частый эффект " << mostCommon << std::endl;
      }
    }
  }
};

void analyzeSingleShop(std::ifstream& file)
{
  std::string line;
  std::string skip;
  std::string name;

  getline(file, line);
  std::istringstream iss(line);
  iss >> skip >> name;

  Shop shop;

  getline(file, line);
  iss = std::istringstream(line);
  int count;
  iss >> skip >> count;

  for (int i = 0; i < count; i++)
  {
    getline(file, line);
    iss = std::istringstream(line);
    shop.addItem(parseItem(iss));
  }

  // empty line at the end
  getline(file, line);

  std::cout << std::format("=== Магазин: {0} ===", name) << std::endl;
  std::cout << std::format("Всего предметов: {0}", count) << std::endl;
  std::cout << std::format("Средняя цена: {:.2f} золота", shop.getAveragePrice()) << std::endl;
  std::cout << std::format("Средний вес: {:.2f} кг", shop.getAverageWeight()) << std::endl;
  std::cout << std::endl;
  shop.analyzeSpecialParams();
}

int main()
{
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
  std::ifstream fs("./shops.txt");
  while (!fs.eof())
  {
    analyzeSingleShop(fs);
    std::cout << std::endl;
  }
}