#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// ==================== COLORS ====================
const std::string GREEN = "\033[32m";
const std::string END_COLOR = "\033[0m";

// ==================== ADDITIONAl FUNCTIONS ====================
template <typename T>
static void PrintVector(std::vector<T>& vec) {
  for (auto& el : vec) {
    std::cout << el << '\n';
  }
}

template <typename T>
static void WriteVector(std::vector<T>& vec, std::ofstream& out) {
  for (auto& el : vec) {
    out << el << '\n';
  }
}

int main() {
  // ==================== PRELIMINARIES ====================
  std::ifstream input("input.txt");
  if (not input.is_open()) {
    std::cout << "File cannot be opened";
  }

  std::vector<std::string> strings;
  std::string string;
  while (std::getline(input, string)) {
    strings.push_back(string);
  }

  input.close();

  int threshold_len;
  std::string word;

  std::cin >> threshold_len;
  std::cin >> word;
  std::cout << '\n';

  // ==================== REMOVING BY INPUT'S LENGTH ====================
  std::function<std::vector<std::string>()> RemoveByLength =
      [strings, threshold_len]() mutable {
        strings.erase(std::remove_if(strings.begin(), strings.end(),
                                     [threshold_len](std::string s) {
                                       return s.length() < threshold_len;
                                     }),
                      strings.end());
        return strings;
      };
  // ==================== REMOVING aA, eE, iI, oO, uU, yY FROM STRINGS
  // ====================
  std::function<std::vector<std::string>()> RemoveVowels = [strings]() mutable {
    for (auto& s : strings) {
      s.erase(std::remove_if(
                  s.begin(), s.end(),
                  [](char chr) {
                    char lower = std::tolower(static_cast<unsigned char>(chr));
                    return lower == 'a' || lower == 'e' || lower == 'i' ||
                           lower == 'o' || lower == 'u' || lower == 'y';
                  }),
              s.end());
    }
    return strings;
  };

  // ==================== SEARCHING FOR STRING THAT CONTAINS SPECIFIED WORD
  // ====================
  std::function<bool()> SearchWord = [&strings, &word]() {
    for (auto& s : strings) {
      if (s.find(word) != -1) {
        return true;
      }
    }
    return false;
  };

  // ==================== COUNTING ALL SYMBOLS EXCLUDE SPECIAL SYMBOLS
  // ====================
  std::function<int()> GetAmountOfSymbols = [&strings]() {
    int cnt = 0;
    for (auto& s : strings) {
      for (auto& chr : s) {
        if (chr != ' ') {
          cnt += 1;
        }
      }
    }
    return cnt;
  };

  // ==================== CREATION NEW VECTOR OF LENGTHS OF STRINGS
  // ====================
  std::function<std::vector<int>()> LengthsOfStrings = [&strings]() {
    std::vector<int> lens;
    for (auto& s : strings) {
      lens.push_back(s.length());
    }
    return lens;
  };

  // ==================== OUTPUT ====================
  std::ofstream output("output.txt");

  WriteVector(strings, output);
  std::cout << GREEN << "Start values: " << END_COLOR << '\n';
  PrintVector(strings);

  std::cout << "\n\n\n\n";

  std::vector<std::string> removedStrings = RemoveByLength();
  WriteVector(removedStrings, output);
  std::cout << GREEN << "Values after removing too short strings: " << END_COLOR
            << '\n';
  PrintVector(removedStrings);

  std::cout << "\n\n\n\n";

  std::vector<std::string> removedLetters = RemoveVowels();
  WriteVector(removedLetters, output);
  std::cout << GREEN
            << "Values after removing vowels (aA, eE, iI, oO, uU, yY): "
            << END_COLOR << '\n';
  PrintVector(removedLetters);

  std::cout << "\n\n\n\n";

  std::cout << GREEN << "Exit code of lambda SearchWord: " << END_COLOR << '\n'
            << SearchWord();
  output << SearchWord();

  std::cout << "\n\n\n\n";

  std::cout << GREEN << "Amount of symbols exclude ' ': " << END_COLOR << '\n'
            << GetAmountOfSymbols();
  output << GetAmountOfSymbols();

  std::cout << "\n\n\n\n";

  std::vector<int> lengthsOfStrings = LengthsOfStrings();
  WriteVector(lengthsOfStrings, output);
  std::cout << GREEN << "Lengths of strings: " << END_COLOR << '\n';
  for (auto& num : lengthsOfStrings) {
    std::cout << num << ' ';
  }

  std::cout << "\n\n\n\n";

  output.close();
}
