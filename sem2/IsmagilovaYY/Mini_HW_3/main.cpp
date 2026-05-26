#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  setlocale(LC_ALL, "Russian");
  //////////////////////////////////////////////
  // считывание всех строк из файла
  std::ifstream inputFile("input.txt");
  if (!inputFile.is_open()) {
    // используем стандартный поток для ошибок
    std::cerr << "Ошибка открытия файла" << std::endl;
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputFile, line)) {
    lines.push_back(line);
  }
  inputFile.close();

  // сохранение исходного вектора для вывода
  std::vector<std::string> originalLines = lines;

  ///////////////////////////////////////////////
  // ввод порога длины строки
  int threshold;
  std::cout << "Введите порог длины строки: ";
  std::cin >> threshold;

  // удаление строк, длина которых меньше порога
  auto removeShortLines = [threshold](const std::string& str) {
    return str.length() < threshold;
  };

  lines.erase(std::remove_if(lines.begin(), lines.end(), removeShortLines),
              lines.end());

  // сохранение строк после удаления коротких
  std::vector<std::string> afterRemoval = lines;

  //////////////////////////////////////////////
  // замена пробелов на подчёркивания
  for (auto& str : lines) {
    std::transform(str.begin(), str.end(), str.begin(), [](char ch) {
      return (ch == ' ') ? '_' : ch;
    });  // тернарный операторЫ
  }
  std::vector<std::string> afterReplace = lines;

  ///////////////////////////////////////////////
  // поиск строки, содержащей заданное слово
  std::string searchWord;
  std::cout << "Введите слово для поиска: ";
  std::cin >> searchWord;

  auto findWord = [&searchWord](const std::string& str) {
    return str.find(searchWord) != std::string::npos;
  };

  auto it = std::find_if(lines.begin(), lines.end(), findWord);
  std::string searchResult;
  if (it != lines.end()) {
    searchResult = *it;
  } else {
    searchResult = "Слово \"" + searchWord + "\" не найдено ни в одной строке";
  }

  ///////////////////////////////////////////////////
  // подсчитывание общего количества символов без учёта подчёркиваний
  int totalCharsWithoutUnderscore = 0;
  for (const auto& str : lines) {
    totalCharsWithoutUnderscore += std::count_if(
        str.begin(), str.end(), [](char ch) { return ch != '_'; });
  }

  ///////////////////////////////////////////////////
  // создание вектора длин строк
  std::vector<int> lineLengths;
  std::transform(lines.begin(), lines.end(), std::back_inserter(lineLengths),
                 [](const std::string& str) { return str.length(); });

  ///////////////////////////////////////////////////
  // запись результатов в output.txt
  std::ofstream outputFile("output.txt");
  if (!outputFile.is_open()) {
    std::cerr << "Ошибка открытия файла" << std::endl;
    return 1;
  }

  outputFile << "Результаты: \n\n";

  // исходный вектор строк
  outputFile << "Исходный вектор:\n";
  for (size_t i = 0; i < originalLines.size(); ++i) {
    outputFile << "Строка " << i + 1 << ": \"" << originalLines[i]
               << "\" (длина: " << originalLines[i].length() << ")\n";
  }

  // вектор строк после удаления коротких строк
  outputFile << "\nВектор строк после удаления коротких (порог = " << threshold
             << "):\n";
  if (afterRemoval.empty()) {
    outputFile << "Все строки были удалены (короче " << threshold
               << " символов)\n";
  } else {
    for (size_t i = 0; i < afterRemoval.size(); ++i) {
      outputFile << "Строка " << i + 1 << ": \"" << afterRemoval[i]
                 << "\" (длина: " << afterRemoval[i].length() << ")\n";
    }
  }

  // вектор строк после замены пробелов на "_"
  outputFile << "\nВектор строк после замены пробелов на \"_\" (Вариант 1):\n";
  for (size_t i = 0; i < afterReplace.size(); ++i) {
    outputFile << "Строка " << i + 1 << ": \"" << afterReplace[i] << "\"\n";
  }

  // результат поиска заданного слова
  outputFile << "\nПоиск слова \"" << searchWord << "\":\n";
  if (it != lines.end()) {
    outputFile << "Слово найдено в строке: \"" << searchResult << "\"\n";
  } else {
    outputFile << searchResult << "\n";
  }

  // общее количество символов без "_"
  outputFile << "\nОбщее количество символов (без учёта символов '_'):\n";
  outputFile << "Всего символов: " << totalCharsWithoutUnderscore << "\n";

  // вектор длин строк
  outputFile << "\nВектор длин строк (после замены пробелов):\n";
  outputFile << "[ ";
  for (size_t i = 0; i < lineLengths.size(); ++i) {
    outputFile << lineLengths[i];
    if (i < lineLengths.size() - 1) outputFile << ", ";
  }
  outputFile << " ]\n";

  outputFile.close();

  std::cout << "\nРезультаты записаны в файл output.txt\n";

  return 0;
}
