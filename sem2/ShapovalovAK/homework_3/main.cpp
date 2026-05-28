#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
  std::ifstream inputFile("input.txt");
  std::vector<std::string> inputLine;
  std::string line;

  while (std::getline(inputFile, line)) {
    inputLine.push_back(line);
  }
  inputFile.close();

  std::vector<std::string> originalLine = inputLine;

  int minLength;
  std::cout << "Введите минимальную длину строки: ";
  std::cin >> minLength;

  std::vector<std::string> cutLines = inputLine;

  cutLines.erase(std::remove_if(cutLines.begin(), cutLines.end(),
                                [minLength](const std::string& str) {
                                  return str.length() <
                                         static_cast<size_t>(minLength);
                                }),
                 cutLines.end());

  std::vector<std::string> noVowelsLines = cutLines;

  std::for_each(
      noVowelsLines.begin(), noVowelsLines.end(), [](std::string& str) {
        str.erase(std::remove_if(
                      str.begin(), str.end(),
                      [](char ch) {
                        char c = std::tolower(static_cast<unsigned char>(ch));

                        return c == 'a' || c == 'A' || c == 'e' || c == 'E' ||
                               c == 'i' || c == 'I' || c == 'o' || c == 'O' ||
                               c == 'u' || c == 'U' || c == 'y' || c == 'Y';
                      }),
                  str.end());
      });
  std::string word;
  std::cout << "Введите слово для поиска: ";
  std::cin >> word;

  auto found = std::find_if(noVowelsLines.begin(), noVowelsLines.end(),
                            [&word](const std::string& str) {
                              return str.find(word) != std::string::npos;
                            });
  int totalChars = 0;

  totalChars = std::accumulate(noVowelsLines.begin(), noVowelsLines.end(), 0,
                               [](int sum, const std::string& str) {
                                 int count = std::count_if(
                                     str.begin(), str.end(),
                                     [](char ch) { return ch != '_'; });

                                 return sum + count;
                               });

  std::vector<int> linesLengths;

  std::transform(noVowelsLines.begin(), noVowelsLines.end(),
                 std::back_inserter(linesLengths), [](const std::string& str) {
                   return static_cast<int>(str.length());
                 });
  std::ofstream outputFile("output.txt");
  outputFile << std::endl << "Исходный вектор строк:" << std::endl << std::endl;

  for (const auto& str : originalLine) {
    outputFile << str << std::endl;
  }

  outputFile << std::endl
             << "После удаления коротких строк:" << std::endl
             << std::endl;

  for (const auto& str : cutLines) {
    outputFile << str << std::endl;
  }

  outputFile << std::endl
             << "После удаления гласных:" << std::endl
             << std::endl;

  for (const auto& str : noVowelsLines) {
    outputFile << str << std::endl;
  }

  outputFile << std::endl
             << "Результат поиска слова " << std::endl
             << word << " :" << std::endl;

  if (found != noVowelsLines.end()) {
    outputFile << std::endl << "Найдена строка: " << *found << std::endl;
  } else {
    outputFile << std::endl << "Строка не найдена" << std::endl;
  }

  outputFile << std::endl
             << "Общее количество символов: " << std::endl
             << totalChars << std::endl;

  outputFile << std::endl << "Вектор длин строк:" << std::endl;

  for (int len : linesLengths) {
    outputFile << len << ' ';
  }

  outputFile << std::endl;

  outputFile.close();

  std::cout << std::endl << "Результат записан в output.txt" << std::endl;

  return 0;
}
