#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int totallynotmain()
{
  std::vector<std::string> lines;
  std::ifstream fin("input.txt");

  if (!fin.is_open())
  {
    std::cerr << "can't find input.txt\n";
    return 1;
  }

  std::string line;
  while (std::getline(fin, line))
  {
    lines.push_back(line);
  }

  fin.close();

  std::vector<std::string> originalLines = lines;

  int minLength;
  std::cout << "min length:\n";
  std::cin >> minLength;

  std::vector<std::string> filteredLines = lines;

  filteredLines.erase(
    std::remove_if(
      filteredLines.begin(),
      filteredLines.end(),
      [minLength](const std::string &s) {
        return s.length() < minLength;
      }
    ),
    filteredLines.end()
  );

  std::vector<std::string> noVowelsLines = filteredLines;

  for (std::string &s: noVowelsLines)
  {
    s.erase(
      std::remove_if(
        s.begin(),
        s.end(),
        [](char c) {
          std::string vowels = "aeiouyAEIOUY";
          return vowels.find(c) != std::string::npos;
        }
      ),
      s.end()
    );
  }

  std::string word;
  std::cout << "Input word to find:\n";
  std::cin >> word;

  auto found = std::find_if(
    filteredLines.begin(),
    filteredLines.end(),
    [&word](const std::string &s) {
      return s.find(word) != std::string::npos;
    }
  );

  std::string searchResult;

  if (found != filteredLines.end())
  {
    searchResult = *found;
  } else
  {
    searchResult = "Строка не найдена";
  }

  int totalChars = 0;

  for (const std::string &s: filteredLines)
  {
    totalChars += std::count_if(
      s.begin(),
      s.end(),
      [](char c) {
        return c != '_';
      }
    );
  }

  std::vector<int> lengths;

  std::transform(
    filteredLines.begin(),
    filteredLines.end(),
    std::back_inserter(lengths),
    [](const std::string &s) {
      return s.length();
    }
  );

  std::ofstream fout("output.txt");

  if (!fout.is_open())
  {
    std::cerr << "Can't open output.txt\n";
    return 1;
  }

  fout << "Исходный вектор:\n";
  for (const std::string &s: originalLines)
  {
    fout << s << '\n';
  }

  fout << "\nпосле удаления коротких:\n";
  for (const std::string &s: filteredLines)
  {
    fout << s << '\n';
  }

  fout << "\nРоскомнадзор запретил букву а...:\n";
  for (const std::string &s: noVowelsLines)
  {
    fout << s << '\n';
  }

  fout << "\nпоиск слова:\n";
  fout << searchResult << '\n';

  fout << "\nсимволов без '_':\n";
  fout << totalChars << '\n';

  fout << "\nвектор длин строк:\n";
  for (int len: lengths)
  {
    fout << len << ' ';
  }

  fout.close();

  return 0;
}
