#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <variant>
#include <vector>

using ItemProperty = std::variant<int, double, std::string>;

class EnchantedObject {
 protected:
  std::string itemName;
  int cost;
  double mass;

 public:
  EnchantedObject(const std::string& n, int c, double m)
      : itemName(n), cost(c), mass(m) {}
  virtual ~EnchantedObject() = default;

  virtual ItemProperty getUniqueProperty() const = 0;
  virtual std::string getCategory() const = 0;

  int getCost() const { return cost; }
  double getMass() const { return mass; }
  std::string getItemName() const { return itemName; }
};

class CombatGear : public EnchantedObject {
  int attack;

 public:
  CombatGear(const std::string& n, int c, double m, int a)
      : EnchantedObject(n, c, m), attack(a) {}

  ItemProperty getUniqueProperty() const override { return attack; }

  std::string getCategory() const override { return "CombatGear"; }
};

class ProtectiveWear : public EnchantedObject {
  int armor;

 public:
  ProtectiveWear(const std::string& n, int c, double m, int a)
      : EnchantedObject(n, c, m), armor(a) {}

  ItemProperty getUniqueProperty() const override { return armor; }

  std::string getCategory() const override { return "ProtectiveWear"; }
};

class MysticBrew : public EnchantedObject {
  double timeActive;

 public:
  MysticBrew(const std::string& n, int c, double m, double t)
      : EnchantedObject(n, c, m), timeActive(t) {}

  ItemProperty getUniqueProperty() const override { return timeActive; }

  std::string getCategory() const override { return "MysticBrew"; }
};

class ArcaneDocument : public EnchantedObject {
  std::string magicalEffect;

 public:
  ArcaneDocument(const std::string& n, int c, double m, const std::string& e)
      : EnchantedObject(n, c, m), magicalEffect(e) {}

  ItemProperty getUniqueProperty() const override { return magicalEffect; }

  std::string getCategory() const override { return "ArcaneDocument"; }
};

struct TradingPost {
  std::string postName;
  std::vector<std::unique_ptr<EnchantedObject>> inventory;
};

std::vector<TradingPost> loadTradingPosts(const std::string& filename) {
  std::vector<TradingPost> posts;
  std::ifstream inputFile(filename);
  std::string textLine;

  TradingPost* currentPost = nullptr;

  while (std::getline(inputFile, textLine)) {
    if (textLine.find("Магазин:") != std::string::npos) {
      posts.emplace_back();
      currentPost = &posts.back();
      currentPost->postName = textLine.substr(9);
    } else if (textLine.find("Предметы:") != std::string::npos) {
      continue;
    } else if (!textLine.empty() && currentPost) {
      std::istringstream lineStream(textLine);
      std::string category, name;
      int priceValue;
      double weightValue;

      lineStream >> category >> name >> priceValue >> weightValue;

      if (category == "Оружие") {
        int power;
        lineStream >> power;
        currentPost->inventory.push_back(
            std::make_unique<CombatGear>(name, priceValue, weightValue, power));
      } else if (category == "Броня") {
        int defenseValue;
        lineStream >> defenseValue;
        currentPost->inventory.push_back(std::make_unique<ProtectiveWear>(
            name, priceValue, weightValue, defenseValue));
      } else if (category == "Зелье") {
        double durationValue;
        lineStream >> durationValue;
        currentPost->inventory.push_back(std::make_unique<MysticBrew>(
            name, priceValue, weightValue, durationValue));
      } else if (category == "Свиток") {
        std::string spellEffect;
        lineStream >> spellEffect;
        currentPost->inventory.push_back(std::make_unique<ArcaneDocument>(
            name, priceValue, weightValue, spellEffect));
      }
    }
  }

  return posts;
}

template <typename ValueType>
ValueType extractValue(const ItemProperty& property) {
  if (std::holds_alternative<ValueType>(property)) {
    return std::get<ValueType>(property);
  }
  return ValueType{};
}

void generateMerchantReport(const std::vector<TradingPost>& posts) {
  for (const auto& post : posts) {
    if (post.inventory.empty()) continue;

    double sumCost = 0;
    double sumMass = 0;

    int combatItems = 0;
    double combatTotal = 0;

    int protectionItems = 0;
    double protectionTotal = 0;

    int brewItems = 0;
    double brewTotal = 0;

    std::map<std::string, int> documentEffects;

    for (const auto& item : post.inventory) {
      sumCost += item->getCost();
      sumMass += item->getMass();

      ItemProperty property = item->getUniqueProperty();
      std::string typeCategory = item->getCategory();

      if (typeCategory == "CombatGear") {
        combatItems++;
        combatTotal += extractValue<int>(property);
      } else if (typeCategory == "ProtectiveWear") {
        protectionItems++;
        protectionTotal += extractValue<int>(property);
      } else if (typeCategory == "MysticBrew") {
        brewItems++;
        brewTotal += extractValue<double>(property);
      } else if (typeCategory == "ArcaneDocument") {
        std::string effect = extractValue<std::string>(property);
        documentEffects[effect]++;
      }
    }

    std::cout << ">>> Торговый пост: " << post.postName << " <<<" << std::endl;
    std::cout << "Общее количество товаров: " << post.inventory.size()
              << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nСредняя стоимость: " << sumCost / post.inventory.size()
              << " золотых" << std::endl;
    std::cout << "Средняя масса: " << sumMass / post.inventory.size() << " кг"
              << std::endl;

    std::cout << "\nАнализ категорий товаров:" << std::endl;

    if (combatItems > 0)
      std::cout << "- Боевое снаряжение: средняя сила = "
                << static_cast<int>(combatTotal / combatItems) << std::endl;
    else
      std::cout << "- Боевое снаряжение: отсутствует" << std::endl;

    if (protectionItems > 0)
      std::cout << "- Защитная экипировка: средняя защита = "
                << static_cast<int>(protectionTotal / protectionItems)
                << std::endl;
    else
      std::cout << "- Защитная экипировка: отсутствует" << std::endl;

    if (brewItems > 0)
      std::cout << "- Мистические отвары: среднее время действия = "
                << brewTotal / brewItems << std::endl;
    else
      std::cout << "- Мистические отвары: отсутствуют" << std::endl;

    if (!documentEffects.empty()) {
      std::string mostPopularEffect;
      int maxCount = 0;

      for (const auto& effectPair : documentEffects) {
        if (effectPair.second > maxCount) {
          maxCount = effectPair.second;
          mostPopularEffect = effectPair.first;
        }
      }
      std::cout << "- Магические свитки: популярный эффект '"
                << mostPopularEffect << "'" << std::endl;
    } else
      std::cout << "- Магические свитки: отсутствуют" << std::endl;
    std::cout << std::endl;
  }
}

int main() {
  std::ofstream dataFile("trading_posts.txt");

  dataFile << "Магазин: Гномьи_Сокровищницы\n";
  dataFile << "Предметы: 6\n";
  dataFile << "Оружие Громовой_Топор 1700 4.2 95\n";
  dataFile << "Оружие Молот_Валькирий 1400 5.8 80\n";
  dataFile << "Броня Стальной_Доспех 900 8.5 75\n";
  dataFile << "Броня Шлем_Невидимки 750 2.3 40\n";
  dataFile << "Зелье Силовой_Отвар 400 0.25 35.5\n";
  dataFile << "Свиток Благословляющий_Свиток 500 0.15 Божественная_Защита\n";

  dataFile << "Магазин: Магическая_Башня\n";
  dataFile << "Предметы: 7\n";
  dataFile << "Оружие Волшебный_Посох 2000 2.2 110\n";
  dataFile << "Броня Мантия_Мудреца 1200 1.5 30\n";
  dataFile << "Зелье Эликсир_Знания 800 0.3 90.0\n";
  dataFile << "Зелье Настой_Ловкости 550 0.28 45.5\n";
  dataFile << "Свиток Свиток_Огненного_Шторма 600 0.22 Огненный_Шторм\n";
  dataFile << "Свиток Свиток_Ледяной_Бури 580 0.26 Ледяная_Буря\n";
  dataFile << "Свиток Свиток_Телепортации 620 0.19 Телепортация\n";

  dataFile << "Магазин: Теневой_Базар\n";
  dataFile << "Предметы: 8\n";
  dataFile << "Оружие Клинок_Тени 1300 1.8 65\n";
  dataFile << "Оружие Призрачный_Лук 1600 2.4 85\n";
  dataFile << "Броня Теневая_Кольчуга 1100 6.2 55\n";
  dataFile << "Броня Перчатки_Ниндзя 950 1.1 25\n";
  dataFile << "Зелье Яд_Гадюки 350 0.12 20.0\n";
  dataFile << "Зелье Отвар_Невидимости 480 0.21 60.5\n";
  dataFile << "Свиток Свиток_Теневого_Змея 520 0.17 Теневой_Змей\n";
  dataFile << "Свиток Свиток_Тишины 440 0.14 Полная_Тишина\n";

  dataFile << "Магазин: Храм_Света\n";
  dataFile << "Предметы: 5\n";
  dataFile << "Оружие Меч_Справедливости 1800 3.8 100\n";
  dataFile << "Броня Латы_Паладина 1500 9.2 90\n";
  dataFile << "Зелье Слезы_Феникса 700 0.35 75.0\n";
  dataFile << "Свиток Свиток_Исцеления 400 0.16 Исцеление\n";
  dataFile << "Свиток Свиток_Святого_Щита 450 0.18 Святой_Щит\n";

  dataFile.close();

  std::cout << "=== ОТЧЕТ ГИЛЬДИИ ТОРГОВЦЕВ МАГИЧЕСКИМИ АРТЕФАКТАМИ ===\n"
            << std::endl;
  std::cout << "Анализ товаров на торговых постах\n" << std::endl;

  auto tradingPosts = loadTradingPosts("trading_posts.txt");
  generateMerchantReport(tradingPosts);

  return 0;
}
