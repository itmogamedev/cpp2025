#include "Adventurer.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

void Adventurer::setId(int& newId) { id = newId; }
void Adventurer::setName(const std::string& newName) { name = newName; }
void Adventurer::setRole(const std::string& newRole) { role = newRole; }
void Adventurer::setLevel(int newLevel) { level = newLevel; }
void Adventurer::setReputation(int newReputation) {
  reputation = newReputation;
  setRank();
}
void Adventurer::setRank() { rank = calculateRank(getReputation()); }

int Adventurer::getId() const { return id; }
std::string Adventurer::getName() const { return name; }
std::string Adventurer::getRole() const { return role; }
int Adventurer::getLevel() const { return level; }
int Adventurer::getReputation() const { return reputation; }
std::string Adventurer::getRank() const { return rank; }

void Adventurer::display() const {
  std::cout << "ID: " << id << "\n";
  std::cout << "Имя: " << name << "\n";
  std::cout << "Роль: " << role << "\n";
  std::cout << "Уровень: " << level << "\n";
  std::cout << "Репутация: " << reputation << "\n";
  std::cout << "Ранг: " << rank << "\n";
  std::cout << "-------------------\n";
}

void Adventurer::writeToFile(std::ofstream& file) const {
  file << "id: " << id << "\n";
  file << "name: " << name << "\n";
  file << "role: " << role << "\n";
  file << "level: " << level << "\n";
  file << "reputation: " << reputation << "\n";
  file << "rank: " << rank << "\n";
  file << "---\n";  // разделитель между записями
}

bool Adventurer::readFromFile(std::ifstream& file) {
  std::string line;

  // Читаем построчно пока не найдем все поля или не кончится файл
  while (std::getline(file, line)) {
    if (line.find("id: ") == 0) {
      this->id = stoi(line.substr(4));
    } else if (line.find("name: ") == 0) {
      this->name = line.substr(6);
    } else if (line.find("role: ") == 0) {
      this->role = line.substr(6);
    } else if (line.find("level: ") == 0) {
      this->level = std::stoi(line.substr(7));
    } else if (line.find("reputation: ") == 0) {
      this->reputation = std::stoi(line.substr(12));
    } else if (line.find("rank: ") == 0) {
      this->rank = line.substr(6);
    } else if (line == "---") {
      return true;  // успешно прочитали одну запись
    }
  }
  return false;  // не удалось прочитать полную запись
}

std::string Adventurer::calculateRank(int reputation) {
  std::map<int, std::string> rankMap = {
      {49, "Новичок"},     {99, "Авантюрист"}, {199, "Страж"},
      {299, "Ветеран"},    {349, "Герой"},     {399, "Прославленный Герой"},
      {INT_MAX, "Легенда"}};

  for (const auto& pair : rankMap) {
    // pair.first - ключ (maxRep)
    // pair.second - значение (rankName)
    if (reputation <= pair.first) {
      return pair.second;
    }
  }
  return "Легенда";
}
