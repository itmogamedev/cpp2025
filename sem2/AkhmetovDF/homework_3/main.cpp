#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main() {
  // ввод порога длины (захват по значению)
  int threshold;
  std::cout << "Enter length threshold: ";
  std::cin >> threshold;
  std::cin.ignore();

  // ввод искомого слова (захват по ссылке)
  std::string word;
  std::cout << "Enter word to search: ";
  std::getline(std::cin, word);

  // чтение исходного файла
  std::ifstream inFile("input.txt");
  if (!inFile) {
    std::cerr << "Error: cannot open input.txt\n";
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inFile, line)) {
    lines.push_back(line);
  }
  inFile.close();

  // сохраняем исходный вектор для вывода
  std::vector<std::string> originalLines = lines;

  // 1.удаление коротких строк (лямбда с захватом по значению)
  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [threshold](const std::string& s) {
                               return s.length() < threshold;
                             }),
              lines.end());

  std::vector<std::string> afterDelete = lines;  // после удаления

  // 2. замена пробелов на '_' (лямбда в transform)
  for (std::string& s : lines) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](char c) { return (c == ' ') ? '_' : c; });
  }

  // 3. поиск строки с заданным словом (лямбда с захватом по ссылке)
  auto it =
      std::find_if(lines.begin(), lines.end(), [&word](const std::string& s) {
        return s.find(word) != std::string::npos;
      });
  bool found = (it != lines.end());
  std::string foundString = found ? *it : "Word not found in any line";

  // 4. подсчёт символов без '_' (лямбды в accumulate и count_if)
  int totalChars = std::accumulate(
      lines.begin(), lines.end(), 0, [](int sum, const std::string& s) {
        return sum + std::count_if(s.begin(), s.end(),
                                   [](char c) { return c != '_'; });
      });

  // 5. создание вектора длин строк (лямбда в transform)
  std::vector<int> lengths;
  std::transform(lines.begin(), lines.end(), std::back_inserter(lengths),
                 [](const std::string& s) { return s.length(); });

  // запись результатов в output.txt
  std::ofstream outFile("output.txt");
  if (!outFile) {
    std::cerr << "Error: cannot create output.txt\n";
    return 1;
  }

  outFile << "Original vector of strings\n";
  for (size_t i = 0; i < originalLines.size(); ++i) {
    outFile << i + 1 << ": " << originalLines[i] << '\n';
  }
  outFile << '\n';

  outFile << "After removing short strings (threshold = " << threshold
          << ")\n";
  for (size_t i = 0; i < afterDelete.size(); ++i) {
    outFile << i + 1 << ": " << afterDelete[i] << '\n';
  }
  outFile << '\n';

  outFile << "After replacing spaces with '_'\n";
  for (size_t i = 0; i < lines.size(); ++i) {
    outFile << i + 1 << ": " << lines[i] << '\n';
  }
  outFile << '\n';

  outFile << "Search result for word \"" << word << "\"\n";
  if (found) {
    outFile << "Line containing the word: \"" << foundString << "\"\n";
  } else {
    outFile << foundString << '\n';
  }
  outFile << '\n';

  outFile << "Total number of characters (excluding '_')\n";
  outFile << totalChars << "\n\n";

  outFile << "Vector of string lengths (after all transformations)\n";
  for (size_t i = 0; i < lengths.size(); ++i) {
    outFile << i + 1 << ": " << lengths[i] << '\n';
  }

  outFile.close();
  std::cout << "Processing complete. Results written to output.txt\n";

  return 0;
}
