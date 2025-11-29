#include "Stats.h"

#include <iomanip>
#include <iostream>
#include <map>

static double avgInt(const std::vector<int>& v) {
  long long s = 0;
  for (int x : v) s += x;
  return v.empty() ? 0 : (double)s / v.size();
}

static double avgDouble(const std::vector<double>& v) {
  double s = 0;
  for (double x : v) s += x;
  return v.empty() ? 0 : s / v.size();
}

static std::string mostFreq(const std::vector<std::string>& v) {
  std::map<std::string, int> f;
  for (auto& s : v) f[s]++;
  int best = 0;
  std::string res;
  for (auto& x : f)
    if (x.second > best) best = x.second, res = x.first;
  return res;
}

void printShopStats(const Shop& shop) {
  using T = MagicItem::Type;

  std::cout << "=== Магазин: " << shop.name << " ===\n";
  size_t n = shop.items.size();
  std::cout << "Всего предметов: " << n << "\n";

  if (!n) return;

  std::vector<int> wDmg, aDef;
  std::vector<double> pDur;
  std::vector<std::string> sEff;

  double sumP = 0, sumW = 0;

  for (auto& it : shop.items) {
    sumP += it->getPrice();
    sumW += it->getWeight();
    auto sp = it->getSpecParam();

    switch (it->getType()) {
      case T::Weapon:
        wDmg.push_back(std::get<int>(sp));
        break;
      case T::Armor:
        aDef.push_back(std::get<int>(sp));
        break;
      case T::Potion:
        pDur.push_back(std::get<double>(sp));
        break;
      case T::Scroll:
        sEff.push_back(std::get<std::string>(sp));
        break;
    }
  }

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Средняя цена: " << sumP / n << "\n";
  std::cout << "Средний вес: " << sumW / n << "\n\n";

  std::cout << "Статистика по предметам:\n";
  wDmg.empty()
      ? std::cout << "- Оружие: нет\n"
      : std::cout << "- Оружие: средний урон = " << avgInt(wDmg) << "\n";

  aDef.empty()
      ? std::cout << "- Броня: нет\n"
      : std::cout << "- Броня: средняя защита = " << avgInt(aDef) << "\n";

  pDur.empty()
      ? std::cout << "- Зелья: нет\n"
      : std::cout << "- Зелья: средняя длительность = " << avgDouble(pDur)
                  << "\n";

  sEff.empty()
      ? std::cout << "- Свитки: нет\n"
      : std::cout << "- Свитки: частый эффект = " << mostFreq(sEff) << "\n";

  std::cout << "\n";
}
