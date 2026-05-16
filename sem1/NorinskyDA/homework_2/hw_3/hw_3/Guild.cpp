#include "Guild.h"

#include <windows.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void Guild::registering_a_new_adventurer() {
  system("cls");
  Adventurer newAdv;

  std::string input;
  int numInput;

  std::cout << "=== Добавление нового авантюриста ===\n";

  std::cout << "ID: ";
  std::cin >> numInput;
  newAdv.setId(numInput);

  std::cin.ignore();  // убираем '\n' из буфера
  std::cout << "Имя: ";
  std::getline(std::cin, input);
  newAdv.setName(input);

  std::cout << "Роль: ";
  std::getline(std::cin, input);
  newAdv.setRole(input);

  std::cout << "Уровень: ";
  std::cin >> numInput;
  newAdv.setLevel(numInput);

  std::cout << "Репутация: ";
  std::cin >> numInput;
  newAdv.setReputation(numInput);

  std::cin.ignore();  // очищаем буфер
  // std::cout << std::endl;
  newAdv.setRank();

  adventurers.push_back(newAdv);
  if (saveToFile()) {
    std::cout << "Авантюрист успешно добавлен!\n" << std::endl;
    go_back_to_the_menu();
  }
}

bool Guild::saveToFile() {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cout << "Не удалось открыть файл для записи: " << filename << "\n";
    return false;
  }

  for (const auto& adventurer : adventurers) {
    adventurer.writeToFile(file);
  }

  file.close();
  std::cout << "Сохранено авантюристов: " << adventurers.size() << "\n";
  return true;
}

//========================== [БАЗА АВАНТЮРИСТОВ]

void Guild::adventurer_base() {
  system("cls");
  if (loadFromFile()) {
    if (adventurers.empty()) {
      std::cout << "База данных пуста!\n";
      go_back_to_the_menu();
    } else {
      std::cout
          << "================< Гильдия Авантюристов Аркадии >================"
          << "\n"
          << "=====: [База авантюристов]" << "\n"
          << "Загружено авантюристов: " << adventurers.size() << "\n";
      for (const auto& adv : adventurers) {
        adv.display();
      }
    }
    go_back_to_the_menu();
  }
}

bool Guild::loadFromFile() {
  std::ifstream file(filename, std::ios::in);
  if (!file.is_open()) {
    std::cout << "Не удалось открыть файл для чтения: " << filename << "\n";
    return false;
  }

  adventurers.clear();  // очищаем текущий список

  Adventurer temp;
  while (temp.readFromFile(file)) {
    adventurers.push_back(temp);
    temp = Adventurer();  // сбрасываем для следующей записи
  }

  file.close();
  return true;
}

//================================ [ПОИСК АВАНТЮРИСТА]

void Guild::adventurer_search() {
  loadFromFile();
  int criterion = selectSearchCriterion();
  if (criterion == 0) go_back_to_the_menu();

  std::string value = getSearchValue(criterion);
  performSearchAndDisplay(criterion, value);
}

int Guild::selectSearchCriterion() {
  system("cls");
  std::cout << "===== [Критерии поиска] =====\n\n"
            << "1 - По ID\n"
            << "2 - По имени\n"
            << "3 - По роли\n"
            << "4 - По уровню\n"
            << "5 - По репутации\n"
            << "6 - По рангу\n"
            << "0 - Назад\n\n"
            << "Ваш выбор: ";

  int choice;
  if (!(std::cin >> choice) || choice < 0 || choice > 6) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Неверный ввод!\n";
    return 0;
  }
  return choice;
}

// Получение значения для поиска
std::string Guild::getSearchValue(int criterion) {
  const std::map<int, std::string> prompts = {{1, "ID"},        {2, "имя"},
                                              {3, "роль"},      {4, "уровень"},
                                              {5, "репутацию"}, {6, "ранг"}};

  std::cout << "\nВведите " << prompts.at(criterion) << " для поиска: ";
  std::string value;
  std::cin.ignore();
  std::getline(std::cin, value);
  return value;
}

// Выполнение поиска и вывод результатов
void Guild::performSearchAndDisplay(int criterion, const std::string& value) {
  auto results = findAdventurers(criterion, value);

  system("cls");
  if (results.empty()) {
    std::cout << "===== [Авантюристы не найдены] =====\n";
  } else {
    std::cout << "===== [Найдено " << results.size()
              << " авантюристов] =====\n\n";
    for (const auto& adv : results) {
      adv.display();
      std::cout << "------------------------\n";
    }
  }

  std::cin.ignore();
}

// Функция поиска
std::vector<Adventurer> Guild::findAdventurers(int criterion,
                                               const std::string& value) {
  std::vector<Adventurer> results;

  for (const auto& adv : adventurers) {
    bool found = false;

    switch (criterion) {
      case 1:
        std::cout << "DEBUG: In case 1!" << std::endl;
        found = (std::to_string(adv.getId()) == value);
        break;
      case 2:
        found = (adv.getName() == value);
        break;
      case 3:
        found = (adv.getRole() == value);
        break;
      case 4:
        found = (std::to_string(adv.getLevel()) == value);
        break;
      case 5:
        found = (std::to_string(adv.getReputation()) == value);
        break;
      case 6:
        found = (adv.getRank() == value);
        break;
    }

    if (found) {
      results.push_back(adv);
    }
  }

  return results;
}

bool Guild::removeById(int& searchId) {
  for (auto it = adventurers.begin(); it != adventurers.end(); ++it) {
    if (it->getId() == searchId) {
      adventurers.erase(it);
      saveToFile();
      return true;
    }
  }
  return false;
}

void Guild::exclusion_from_the_guild() {
  loadFromFile();
  int remove_ID;
  bool flag = false;
  system("cls");
  std::cout << "=====: [Введите ID для исключения авантюриста..]" << std::endl;
  while (!flag) {
    std::cin >> remove_ID;

    if (std::cin.fail()) {           // если ввод неудачен
      std::cin.clear();              // сбрасываем флаги ошибок
      std::cin.ignore(10000, '\n');  // очищаем буфер
      std::cout << "Неверный ввод! Пожалуйста, введите число от 1 до 6: "
                << std::endl;
      continue;
    } else {
      if (removeById(remove_ID)) {
        std::cout << "=====: [Авантюрист исключён!]" << std::endl;
      } else
        std::cout << "=====: [Такого авантюриста нет в базе авантюристов..]"
                  << std::endl;
      flag = true;
    }
  }
  go_back_to_the_menu();
}

// Поиск авантюриста по ID
Adventurer* Guild::findById(int& searchId) {
  for (auto& adv : adventurers) {
    if (adv.getId() == searchId) {
      return &adv;
    }
  }
  return nullptr;
}

void Guild::accrual_of_reputation() {
  system("cls");
  int _ID;
  std::cout << "=====: [Введите ID авантюриста, у которого хотите изменить "
               "кол-во очков репутации..]"
            << std::endl;
  std::cin >> _ID;
  Adventurer* temp = findById(_ID);
  if (temp) {
    int new_reputation_count;
    std::cout << "=====: [Введите кол-во очков репутации..]" << std::endl;
    std::cin >> new_reputation_count;
    temp->setReputation(new_reputation_count);
    saveToFile();
    go_back_to_the_menu();
  }
}

void Guild::go_back_to_the_menu() {
  int exit_the_menu;
  std::cout << std::endl << "Вернутся в меню? --> 0" << std::endl;
  std::cin >> exit_the_menu;
  if (exit_the_menu == 0) menu();
}

void Guild::menu() {
  setlocale(LC_ALL, "ru");
  system("cls");
  int menu_selection;
  bool flag = false;

  std::cout << "################> Добро пожаловать в Гильдию Авантюристов "
               "Аркадии! <################"
            << "\n"
            << "=====: [Меню на выбор]"
            << "\n"
            << "\n"
            << "1 - Добавить нового авантюриста" << "\n"
            << "2 - База авантюристов" << "\n"
            << "3 - Поиск авантюриста" << "\n"
            << "4 - Исключение авантюриста" << "\n"
            << "5 - Начисление репутации" << "\n";

  while (!flag) {
    std::cin >> menu_selection;

    if (std::cin.fail()) {               // если ввод неудачен
      std::cin.clear();                  // сбрасываем флаги ошибок
      std::cin.ignore(10 + -000, '\n');  // очищаем буфер
      std::cout << "Неверный ввод! Пожалуйста, введите число от 1 до 6: "
                << std::endl;
      continue;
    }

    switch (menu_selection) {
      case 1:
        registering_a_new_adventurer();
        flag = true;
        break;
      case 2:
        adventurer_base();
        flag = true;
        break;
      case 3:
        adventurer_search();
        flag = true;
        break;
      case 4:
        exclusion_from_the_guild();
        flag = true;
        break;
      case 5:
        accrual_of_reputation();
        flag = true;
        break;
      default:
        std::cout << "Неверно набран номер, попробуйте ещё раз!" << std::endl;
        break;
    }
  }
}
