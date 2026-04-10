#pragma once
#include <string>

class Adventurer {
  int id;
  std::string name;
  std::string role;
  unsigned int level;
  int reputation = 0;
  std::string rank;

 public:
  Adventurer(int id_ = 0, std::string name_ = "", std::string role_ = "",
             int level_ = 0, int reputation_ = 0)
      : id(id_),
        name(name_),
        role(role_),
        level(level_),
        reputation(reputation_) {}
  bool readFromFile(std::ifstream& file);
  void display() const;
  void writeToFile(std::ofstream& file) const;
  std::string calculateRank(int reputation);

  void setId(int& newId);
  void setName(const std::string& newName);
  void setRole(const std::string& newRole);
  void setLevel(int newLevel);
  void setReputation(int newReputation);
  void setRank();

  int getId() const;
  std::string getName() const;
  std::string getRole() const;
  int getLevel() const;
  int getReputation() const;
  std::string getRank() const;
};
