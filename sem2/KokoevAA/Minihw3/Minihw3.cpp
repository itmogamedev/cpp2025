#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readLinesFromFile(const std::string& fileName) {
  std::ifstream input(fileName);
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(input, line)) {
    lines.push_back(line);
  }

  return lines;
}

bool isVowel(char symbol) {
  const std::string vowels = "aeiouyAEIOUY";
  return vowels.find(symbol) != std::string::npos;
}

std::string toLower(const std::string& text) {
  std::string result = text;

  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char symbol) {
                   return static_cast<char>(std::tolower(symbol));
                 });

  return result;
}

std::vector<std::string> removeShortLines(const std::vector<std::string>& lines,
                                          int minLength) {
  std::vector<std::string> result;

  std::copy_if(lines.begin(), lines.end(), std::back_inserter(result),
               [minLength](const std::string& line) {
                 return static_cast<int>(line.size()) >= minLength;
               });

  return result;
}

std::vector<std::string> removeVowelsFromLines(
    const std::vector<std::string>& lines) {
  std::vector<std::string> result = lines;

  std::for_each(result.begin(), result.end(), [](std::string& line) {
    line.erase(std::remove_if(line.begin(), line.end(),
                              [](char symbol) { return isVowel(symbol); }),
               line.end());
  });

  return result;
}

std::vector<std::string> findLinesWithWord(
    const std::vector<std::string>& lines, const std::string& word) {
  std::vector<std::string> result;
  std::string lowerWord = toLower(word);

  std::copy_if(lines.begin(), lines.end(), std::back_inserter(result),
               [&lowerWord](const std::string& line) {
                 return toLower(line).find(lowerWord) != std::string::npos;
               });

  return result;
}

int countCharactersWithoutUnderscore(const std::vector<std::string>& lines) {
  int count = 0;

  std::for_each(lines.begin(), lines.end(), [&count](const std::string& line) {
    count += static_cast<int>(std::count_if(
        line.begin(), line.end(), [](char symbol) { return symbol != '_'; }));
  });

  return count;
}

std::vector<int> getLineLengths(const std::vector<std::string>& lines) {
  std::vector<int> lengths;

  std::transform(
      lines.begin(), lines.end(), std::back_inserter(lengths),
      [](const std::string& line) { return static_cast<int>(line.size()); });

  return lengths;
}

void writeStringVector(std::ofstream& output, const std::string& title,
                       const std::vector<std::string>& lines) {
  output << title << "\n";

  for (const std::string& line : lines) {
    output << line << "\n";
  }

  output << "\n";
}

void writeIntVector(std::ofstream& output, const std::string& title,
                    const std::vector<int>& numbers) {
  output << title << "\n";

  for (int number : numbers) {
    output << number << "\n";
  }

  output << "\n";
}

void solve() {
  const std::string inputFileName = "input.txt";
  const std::string outputFileName = "output.txt";

  int minLength;
  std::string searchWord;

  std::cout << "Enter minimum line length: ";
  std::cin >> minLength;

  std::cout << "Enter search word: ";
  std::cin >> searchWord;

  std::vector<std::string> sourceLines = readLinesFromFile(inputFileName);
  std::vector<std::string> filteredLines =
      removeShortLines(sourceLines, minLength);
  std::vector<std::string> withoutVowels = removeVowelsFromLines(filteredLines);
  std::vector<std::string> foundLines =
      findLinesWithWord(sourceLines, searchWord);
  int totalCharacters = countCharactersWithoutUnderscore(withoutVowels);
  std::vector<int> lineLengths = getLineLengths(sourceLines);

  std::ofstream output(outputFileName);

  writeStringVector(output, "Исходный вектор строк:", sourceLines);
  writeStringVector(
      output, "Вектор строк после удаления коротких строк:", filteredLines);
  writeStringVector(output,
                    "Вектор строк после удаления гласных букв:", withoutVowels);
  writeStringVector(output, "Результат поиска заданного слова:", foundLines);

  output << "Общее количество символов без \"_\"\n";
  output << totalCharacters << "\n\n";

  writeIntVector(output, "Вектор длин строк:", lineLengths);
}

int main() {
  solve();
  return 0;
}
