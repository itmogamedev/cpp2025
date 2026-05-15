#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

void fileWork() {
  std::ifstream inputFile("input.txt");
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputFile, line)) {
    lines.push_back(line);
  }
  inputFile.close();

  std::vector<std::string> original = lines;

  int deleteByLenght;
  std::cout << "Введите порог ввода" << std::endl;
  std::cin >> deleteByLenght;

  auto removeLines = [deleteByLenght](const std::string& str) {
    return str.length() < deleteByLenght;
  };
  lines.erase(std::remove_if(lines.begin(), lines.end(), removeLines),
              lines.end());

  std::vector<std::string> afterDelete = lines;

  for (auto& str : lines) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](char c) { return c == ' ' ? '_' : c; });
  }

  std::vector<std::string> afterRemove = lines;

  std::string search;
  std::cout << "Введите слово, которое хотите найти" << std::endl;
  std::cin >> search;

  auto findWord = [&search](const std::string& str) {
    return str.find(search) != std::string::npos;
  };

  std::string searchRes = "Не найдено";
  for (const auto& str : lines) {
    if (findWord(str)) {
      searchRes = "Слово " + search + " найдено в строке " + str;
      break;
    }
  }

  int totalWOutUnderscore = 0;
  for (const auto& str : lines) {
    totalWOutUnderscore +=
        std::count_if(str.begin(), str.end(), [](char c) { return c != '_'; });
  }

  std::vector<int> lineLenght;
  std::transform(lines.begin(), lines.end(), std::back_inserter(lineLenght),
                 [](const std::string& str) { return str.length(); });

  std::ofstream outputFile("output.txt");

  outputFile << "1) Начальные строки\n";
  for (int i = 0; i < original.size(); i++) {
    outputFile << "  " << i + 1 << ". " << original[i] << "\n";
  }

  outputFile << "2) Строки после удаления коротких строк (порог = "
             << deleteByLenght << ")\n";
  if (afterDelete.empty()) {
    outputFile << "None\n";
  } else {
    for (int i = 0; i < afterDelete.size(); i++) {
      outputFile << "  " << i + 1 << ". " << afterDelete[i] << "\n";
    }
  }

  outputFile << "3) Строки после замены пробелов на '_'\n";
  if (afterRemove.empty()) {
    outputFile << "None\n";
  } else {
    for (int i = 0; i < afterRemove.size(); i++) {
      outputFile << "  " << i + 1 << ". " << afterRemove[i] << "\n";
    }
  }

  outputFile << "4) Результат поиска слова - " << search << "\n";
  outputFile << "  " << searchRes << "\n";

  outputFile << "5) Кол-во символов во всех строках без учета '_'\n";
  outputFile << "  " << totalWOutUnderscore << "\n";

  outputFile << "6) Вектор длин строк\n";
  if (lineLenght.empty()) {
    outputFile << "None";
  } else {
    for (int i = 0; i < lineLenght.size(); i++) {
      outputFile << "  " << i + 1 << ". " << lineLenght[i] << "\n";
    }
  }

  outputFile.close();
  std::cout << "Работа завершена, проверте файл output.txt";
}

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  fileWork();
  return 0;
}
