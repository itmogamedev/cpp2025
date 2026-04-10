#pragma once
#include <string>
#include <vector>

#include "Adventurer.h"

class Guild {
  std::vector<Adventurer> adventurers;
  std::string filename;

 public:
  Guild(const std::string& file) : filename(file) {}
  void menu();
  void adventurer_base();
  bool loadFromFile();
  void registering_a_new_adventurer();
  bool saveToFile();
  void adventurer_search();
  void go_back_to_the_menu();
  int selectSearchCriterion();
  std::string getSearchValue(int criterion);
  void performSearchAndDisplay(int criterion, const std::string& value);
  std::vector<Adventurer> findAdventurers(int criterion,
                                          const std::string& value);
  bool removeById(int& searchId);
  void exclusion_from_the_guild();
  Adventurer* findById(int& searchId);
  void accrual_of_reputation();
};
