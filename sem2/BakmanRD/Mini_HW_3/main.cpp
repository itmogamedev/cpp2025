#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::ifstream inFile("input.txt");
  if (!inFile) {
    std::cerr << "Cannot open input.txt" << std::endl;
    return 1;
  }

  std::vector<std::string> originalLines;
  std::string line;
  while (std::getline(inFile, line)) {
    originalLines.push_back(line);
  }
  inFile.close();

  std::ofstream outFile("output.txt");
  if (!outFile) {
    std::cerr << "Cannot open output.txt" << std::endl;
    return 1;
  }

  outFile << "Original file:\n";
  for (const auto& s : originalLines) outFile << s << '\n';
  outFile << '\n';

  std::cout << "Enter the min line length: ";
  size_t threshold;
  std::cin >> threshold;
  std::cin.ignore();

  std::vector<std::string> filteredLines = originalLines;
  auto isShort = [threshold](const std::string& s) {
    return s.length() < threshold;
  };
  auto it = std::remove_if(filteredLines.begin(), filteredLines.end(), isShort);
  filteredLines.erase(it, filteredLines.end());

  outFile << "All the lines longer than " << threshold << " symbols\n";
  for (const auto& s : filteredLines) outFile << s << '\n';
  outFile << '\n';

  std::vector<std::string> modifiedLines = filteredLines;
  auto isVowel = [](char c) {
    const std::string vowels = "aeiouyAEIOUY";
    return vowels.find(c) != std::string::npos;
  };

  for (auto& s : modifiedLines) {
    s.erase(std::remove_if(s.begin(), s.end(), isVowel), s.end());
    std::replace(s.begin(), s.end(), ' ', '_');
  }

  outFile << "All the lines after the changes \"_\":\n";
  for (const auto& s : modifiedLines) outFile << s << '\n';
  outFile << '\n';

  std::cout << "Enter the word to be searched: ";
  std::string searchWord;
  std::getline(std::cin, searchWord);

  auto containsWord = [&searchWord](const std::string& s) {
    return s.find(searchWord) != std::string::npos;
  };

  auto foundIt =
      std::find_if(modifiedLines.begin(), modifiedLines.end(), containsWord);
  outFile << "Result of the search of the word \"" << searchWord << "\": ";
  if (foundIt != modifiedLines.end()) {
    outFile << "found: " << *foundIt << '\n';
  } else {
    outFile << "not found\n";
  }
  outFile << '\n';

  long totalCharsNoUnderscore = std::accumulate(
      modifiedLines.begin(), modifiedLines.end(), 0L,
      [](long sum, const std::string& s) {
        return sum + std::count_if(s.begin(), s.end(),
                                   [](char c) { return c != '_'; });
      });

  outFile << "Total symbol count w/o '_': " << totalCharsNoUnderscore << "\n\n";

  std::vector<size_t> lengths;
  lengths.reserve(modifiedLines.size());
  std::transform(modifiedLines.begin(), modifiedLines.end(),
                 std::back_inserter(lengths),
                 [](const std::string& s) { return s.length(); });

  outFile << "The length of all the lines:\n";
  for (size_t len : lengths) outFile << len << ' ';
  outFile << '\n';

  outFile.close();
  return 0;
}