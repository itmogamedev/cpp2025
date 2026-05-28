#include <windows.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::ifstream inFile("input.txt");
  if (!inFile.is_open()) {
    std::cerr << "Ошибка: не удалось открыть input.txt" << std::endl;
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inFile, line)) {
    lines.push_back(line);
  }
  inFile.close();

  std::cout << "Исходный вектор строк:\n";
  for (const auto& s : lines) {
    std::cout << "\"" << s << "\"\n";
  }

  // 1. Ввод порога длины строки
  int threshold;
  std::cout << "Введите порог длины строки (удаляются строки короче этого "
               "значения): ";
  std::cin >> threshold;

  // 2. Удаление строк, длина которых меньше порога (лямбда с захватом по
  // значению)
  auto it = std::remove_if(
      lines.begin(), lines.end(),
      [threshold](const std::string& s) { return s.length() < threshold; });
  lines.erase(it, lines.end());

  std::cout << "\nПосле удаления коротких строк:\n";
  for (const auto& l : lines) {
    std::cout << "\"" << l << "\"\n";
  }

  // 3. Удаление гласных букв (a, e, i, o, u, y в любом регистре)
  // Функция для проверки, является ли символ гласной
  auto isVowel = [](char ch) -> bool {
    char lower = std::tolower(ch);
    return (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' ||
            lower == 'u' || lower == 'y');
  };

  std::vector<std::string> linesWithoutVowels = lines;
  for (auto& str : linesWithoutVowels) {
    std::string newStr;
    for (char ch : str) {
      if (!isVowel(ch)) {
        newStr += ch;
      }
    }
    str = newStr;
  }

  std::cout << "\nПосле удаления гласных:\n";
  for (const auto& l : linesWithoutVowels) {
    std::cout << "\"" << l << "\"\n";
  }

  // 4. Поиск строки, содержащей заданное слово (лямбда с захватом по ссылке)
  std::string searchWord;
  std::cout << "\nВведите слово для поиска: ";
  std::cin >> searchWord;

  auto foundIt = std::find_if(lines.begin(), lines.end(),
                              [&searchWord](const std::string& s) {
                                return s.find(searchWord) != std::string::npos;
                              });

  std::string searchResult;
  if (foundIt != lines.end()) {
    searchResult = "Найдена строка: \"" + *foundIt + "\"";
  } else {
    searchResult = "Строка, содержащая \"" + searchWord + "\", не найдена";
  }

  // 5. Подсчёт общего количества символов во всех строках (без учёта '_')
  int totalCharsNoUnderscore = 0;
  for (const auto& str : lines) {
    for (char ch : str) {
      if (ch != '_') {
        totalCharsNoUnderscore++;
      }
    }
  }

  // 6. Создание нового вектора целых чисел, содержащего длины всех строк
  std::vector<int> lineLengths;
  for (const auto& str : lines) {
    lineLengths.push_back((str.length()));
  }

  // Запись всех результатов в output.txt
  std::ofstream outFile("output.txt");
  if (!outFile.is_open()) {
    std::cerr << "Ошибка: не удалось создать output.txt" << std::endl;
    return 1;
  }

  outFile << "========== РЕЗУЛЬТАТЫ РАБОТЫ ПРОГРАММЫ ==========\n\n";

  // Исходный вектор строк
  outFile << "1. Исходный вектор строк:\n";
  std::ifstream originalFile("input.txt");
  std::string origLine;
  int idx = 1;
  while (std::getline(originalFile, origLine)) {
    outFile << "   " << idx++ << ". \"" << origLine << "\"\n";
  }
  originalFile.close();
  outFile << "\n";

  // Вектор после удаления коротких строк
  outFile << "2. Вектор строк после удаления строк короче " << threshold
          << ":\n";
  for (size_t i = 0; i < lines.size(); ++i) {
    outFile << "   " << i + 1 << ". \"" << lines[i] << "\"\n";
  }
  outFile << "\n";

  // Вектор после удаления гласных
  outFile
      << "3. Вектор строк после удаления гласных букв (a, e, i, o, u, y):\n";
  for (size_t i = 0; i < linesWithoutVowels.size(); ++i) {
    outFile << "   " << i + 1 << ". \"" << linesWithoutVowels[i] << "\"\n";
  }
  outFile << "\n";

  // Результат поиска
  outFile << "4. Результат поиска слова \"" << searchWord << "\":\n";
  outFile << "   " << searchResult << "\n\n";

  // Общее количество символов без '_'
  outFile << "5. Общее количество символов (без учёта символов подчёркивания "
             "'_'):\n";
  outFile << "   " << totalCharsNoUnderscore << "\n\n";

  // Вектор длин строк
  outFile << "6. Вектор длин строк:\n";
  for (size_t i = 0; i < lineLengths.size(); ++i) {
    outFile << "   " << i + 1 << ". " << lineLengths[i] << "\n";
  }

  outFile.close();

  std::cout << "\nРезультаты записаны в файл output.txt\n";

  return 0;
}
