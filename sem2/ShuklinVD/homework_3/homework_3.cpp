#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void run() {
  std::vector<std::string> lines;
  std::ifstream fin("input.txt");
  std::string line;
  while (std::getline(fin, line)) {
    lines.push_back(line);
  }
  fin.close();

  std::vector<std::string> original = lines;

  int threshold;
  std::string word;
  std::cout << "Введите минимальную длину строки: ";
  std::cin >> threshold;
  std::cout << "Введите слово для поиска (eng, pls): ";
  std::cin >> word;

  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [threshold](const std::string& s) {
                               return s.length() < threshold;
                             }),
              lines.end());

  std::vector<std::string> after_short = lines;

  std::for_each(lines.begin(), lines.end(), [](std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(),
                           [](char c) {
                             char lc = std::tolower(c);
                             return lc == 'a' || lc == 'e' || lc == 'i' ||
                                    lc == 'o' || lc == 'u' || lc == 'y';
                           }),
            s.end());
  });

  auto it = std::find_if(original.begin(), original.end(),
                         [&word](const std::string& s) {
                           return s.find(word) != std::string::npos;
                         });
  std::string found;
  if (it != original.end()) {
    found = *it;
  } else {
    found = "[Не найдено]";
  }

  int total = std::accumulate(
      lines.begin(), lines.end(), 0, [](int acc, const std::string& s) {
        return acc + std::count_if(s.begin(), s.end(),
                                   [](char c) { return c != ' '; });
      });

  std::vector<int> lengths(lines.size());

  std::transform(lines.begin(), lines.end(), lengths.begin(),
                 [](const std::string& s) { return s.length(); });

  std::ofstream fout("output.txt");
  fout << "=== Исходный вектор строк ===\n";
  for (const auto& s : original) fout << s << "\n";

  fout << "\n=== После удаления коротких строк (длина < " << threshold
       << ") ===\n";
  for (const auto& s : after_short) fout << s << "\n";

  fout << "\n=== После удаления гласных ===\n";
  for (const auto& s : lines) fout << s << "\n";

  fout << "\n=== Поиск слова \"" << word << "\" в исходных строках ===\n";
  fout << found << "\n";

  fout << "\n=== Общее число символов (без пробелов, в новых строках) ===\n";
  fout << total << "\n";

  fout << "\n=== Вектор длин строк (новых) ===\n";
  for (int len : lengths) fout << len << " ";
  fout << "\n";

  fout.close();
}

int main() {
  setlocale(LC_ALL, "");
  run();
}
