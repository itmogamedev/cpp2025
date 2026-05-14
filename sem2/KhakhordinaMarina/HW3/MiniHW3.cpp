#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
  // Считать все строки из файла input.txt в вектор std::vector<std::string>
  std::ifstream inFile("input.txt");
  std::vector<std::string> v1;
  std::string line;

  while (std::getline(inFile, line)) {
    v1.push_back(line);
  }
  inFile.close();

  // Ввод данных пользователем
  int num;
  std::cout << "Enter length: ";
  std::cin >> num;

  std::string word;
  std::cout << "Enter word: ";
  std::cin.ignore();
  std::getline(std::cin, word);

  std::ofstream outFile("output.txt");

  // Вывести в файл output.txt: Исходный вектор строк
  outFile << "Original lines:\n";
  for (int i = 0; i < v1.size(); i++) {
    outFile << v1[i] << "\n";
  }
  outFile << "\n";

  // Удаление всех строк, длина которых меньше заданного пользователем порога. Использовать лямбду с захватом по значению
  std::vector<std::string> v2;
  auto isShort = [num](std::string s) {
    return s.length() < num;
    };

  for (int i = 0; i < v1.size(); i++) {
    if (isShort(v1[i]) == false) {
      v2.push_back(v1[i]);
    }
  }

  // Вывести в файл output.txt: Вектор строк после удаления коротких строк
  outFile << "After removing short lines:\n";
  for (int i = 0; i < v2.size(); i++) {
    outFile << v2[i] << "\n";
  }
  outFile << "\n";

  // ВАРИАНТ 1: Замену в каждой строке всех пробелов на символ подчёркивания “_”
  auto replaceSpaces = [](std::string& s) {
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == ' ') {
        s[i] = '_';
      }
    }
    };

  for (int i = 0; i < v2.size(); i++) {
    replaceSpaces(v2[i]);
  }

  // Вывести в файл output.txt: Вектор строк после замены пробелов на “_”
  outFile << "After replacing spaces:\n";
  for (int i = 0; i < v2.size(); i++) {
    outFile << v2[i] << "\n";
  }
  outFile << "\n";

  // Поиск строки, содержащей заданное пользователем слово. Использовать лямбду с захватом по ссылке
  std::string res = "Word not found.";
  auto findWord = [&word](std::string s) {
    return s.find(word) != std::string::npos;
    };

  for (int i = 0; i < v2.size(); i++) {
    if (findWord(v2[i]) == true) {
      res = "Found: " + v2[i];
      break;
    }
  }

  // Вывести в файл output.txt: Результат поиска заданного слова
  outFile << "Search result:\n" << res << "\n\n";

  // Подсчёт общего количества символов во всех строках (без учёта символом подчёркиваний “_”)
  int total = 0;
  auto countValidChars = [](std::string s) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] != '_') {
        count++;
      }
    }
    return count;
    };

  for (int i = 0; i < v2.size(); i++) {
    total = total + countValidChars(v2[i]);
  }

  // Вывести в файл output.txt: Общее количество символов без “_”
  outFile << "Total characters without '_': " << total << "\n\n";

  // Создание нового вектора целых чисел, содержащего длины всех строк
  std::vector<int> v3;
  auto getLength = [](std::string s) {
    return (int)s.length();
    };

  for (int i = 0; i < v2.size(); i++) {
    v3.push_back(getLength(v2[i]));
  }

  // Вывести в файл output.txt: Вектор длин строк
  outFile << "Line lengths:\n";
  for (int i = 0; i < v3.size(); i++) {
    outFile << v3[i] << " ";
  }
  outFile << "\n";

  outFile.close();
  std::cout << "Done!" << std::endl;
  return 0;
}
