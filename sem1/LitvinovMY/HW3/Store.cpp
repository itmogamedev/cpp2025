#include "Store.h"

#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "MagicItem.h"

bool Store::AddItem(MagicItem* mi) { return true; }

std::string Store::PrintStatistics() {
  int count = 0;
  double price_total = 0.0;
  double weight_total = 0.0;

  int weapon_count = 0;
  int weapon_dmg_total = 0;

  int armor_count = 0;
  int armor_def_total = 0;

  int potion_count = 0;
  double potion_dur_total = 0.0;

  std::map<std::string, int> scroll_effects;

  // temp value
  std::string effect;

  for (auto i : items) {
    count++;

    price_total += i->get_price();
    weight_total += i->get_weight();

    switch (i->get_type()) {
      case kWeapon:
        weapon_count++;
        weapon_dmg_total += std::get<int>(i->get_special_param());
        break;

      case kArmor:
        armor_count++;
        armor_def_total = std::get<int>(i->get_special_param());
        break;

      case kPotion:
        potion_count++;
        potion_dur_total = std::get<double>(i->get_special_param());
        break;

      case kScroll:
        effect = std::get<std::string>(i->get_special_param());
        if (scroll_effects.contains(effect)) {
          scroll_effects[effect]++;
        } else {
          scroll_effects.insert({effect, 1});
        }
        break;
    }
  }

  std::ostringstream out;
  // TODO: output here
  return out.str();
}

Store::~Store() {}