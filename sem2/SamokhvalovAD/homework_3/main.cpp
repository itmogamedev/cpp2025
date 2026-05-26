#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readFile(std::string fileName) {
  std::ifstream in(fileName);

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(in, line)) {
    lines.push_back(line);
  }
  return lines;
}

std::pair<int, std::string> getData() {
  int limit;
  std::string word;

  std::cout << "Enter minimum line length: ";
  std::cin >> limit;

  std::cout << "Enter word to search: ";
  std::cin >> word;

  return std::make_pair(limit, word);
}

std::vector<std::string> deleteByLimit(std::vector<std::string> vector,
                                       int limit) {
  vector.erase(std::remove_if(vector.begin(), vector.end(),
                              [limit](const std::string& s) {
                                return static_cast<int>(s.length()) < limit;
                              }),
               vector.end());
  return vector;
}

std::vector<std::string> deleteVovels(std::vector<std::string> vector) {
  for (std::string& s : vector) {
    s.erase(std::remove_if(s.begin(), s.end(),
                           [](char ch) {
                             ch = static_cast<char>(
                                 std::tolower(static_cast<unsigned char>(ch)));
                             return ch == 'a' || ch == 'e' || ch == 'i' ||
                                    ch == 'o' || ch == 'u' || ch == 'y';
                           }),
            s.end());
  }
  return vector;
}

std::string findWord(std::vector<std::string> vector, std::string word) {
  std::string answer = "Not found";
  auto isWord = [&word](const std::string& s) {
    return s.find(word) != std::string::npos;
  };
  auto it = std::find_if(vector.begin(), vector.end(), isWord);
  if (it != vector.end()) {
    answer = *it;
  }
  return answer;
}

int countAllChars(std::vector<std::string> vector) {
  int count = 0;
  for (const std::string& s : vector) {
    count +=
        std::count_if(s.begin(), s.end(), [](char ch) { return ch != '_'; });
  }
  return count;
}

std::vector<int> countAllCharsInLines(std::vector<std::string> vector) {
  std::vector<int> lengths;
  std::transform(
      vector.begin(), vector.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });
  return lengths;
}

void printStringVector(std::ofstream& out, std::vector<std::string> vector,
                       std::string title) {
  out << title << '\n';
  for (size_t i = 0; i < vector.size(); ++i) {
    out << vector[i] << '\n';
  }
  out << '\n';
}

void printIntVector(std::ofstream& out, std::vector<int> vector,
                    std::string title) {
  out << title << '\n';
  for (size_t i = 0; i < vector.size(); ++i) {
    out << vector[i] << '\n';
  }
}

void printAll(std::ofstream& out, std::vector<std::string> originalVector,
              std::vector<std::string> vectorDeleteByLimit,
              std::vector<std::string> vectorDeleteVovels,
              std::string foundWord, int countChars,
              std::vector<int> countCharsInLines) {
  printStringVector(out, originalVector, "Original vector:");
  printStringVector(out, vectorDeleteByLimit,
                    "Vector after deleting short lines:");
  printStringVector(out, vectorDeleteVovels, "Vector after deleting vowels:");
  out << "Search result:\n" << foundWord << "\n\n";
  out << "Total number of characters without '_':\n" << countChars << "\n\n";
  printIntVector(out, countCharsInLines, "Vector of line lengths:");
}

int main() {
  std::vector<std::string> input = readFile("input.txt");
  std::ofstream out("output.txt");
  std::pair<int, std::string> data = getData();
  int limit = data.first;
  std::string word = data.second;

  std::vector<std::string> vectorDeleteByLimit = deleteByLimit(input, limit);
  std::vector<std::string> vectorDeleteVovels = deleteVovels(input);
  std::string foundWord = findWord(input, word);
  int countChars = countAllChars(input);
  std::vector<int> countCharsInLines = countAllCharsInLines(input);

  printAll(out, input, vectorDeleteByLimit, vectorDeleteVovels, foundWord,
           countChars, countCharsInLines);

  return 0;
}