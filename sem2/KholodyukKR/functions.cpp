#include "functions.h"

#include <fstream>
#include <iostream>

void runTask() {
  std::vector<std::string> originalLines;
  std::ifstream inFile("input.txt");

  if (!inFile.is_open()) {
    std::cerr << "Error" << std::endl;
    return;
  }

  std::string currentLine;
  while (std::getline(inFile, currentLine)) {
    originalLines.push_back(currentLine);
  }
  inFile.close();

  int threshold = 0;
  std::cout << "Enter string length: ";
  std::cin >> threshold;

  auto isShorterThan = [threshold](const std::string& checkedString) {
    return static_cast<int>(checkedString.length()) < threshold;
  };

  // Удаление коротких строк
  std::vector<std::string> linesAfterRemoval;
  for (const auto& lineItem : originalLines) {
    if (!isShorterThan(lineItem)) {
      linesAfterRemoval.push_back(lineItem);
    }
  }

  // замена _
  std::vector<std::string> linesAfterVariant = linesAfterRemoval;
  for (auto& processString : linesAfterVariant) {
    for (size_t i = 0; i < processString.length(); ++i) {
      if (processString[i] == ' ') {
        processString[i] = '_';
      }
    }
  }

  // поиск строки
  std::string searchWord;
  std::cout << "Enter word to search: ";
  std::cin >> searchWord;

  std::string searchResult = "Word not found";
  auto findWordLambda = [&searchWord,
                         &searchResult](const std::string& targetString) {
    if (targetString.find(searchWord) != std::string::npos) {
      searchResult = "Found line: " + targetString;
    }
  };

  for (const auto& targetString : linesAfterVariant) {
    if (searchResult == "Word not found") {
      findWordLambda(targetString);
    }
  }

  // Подсчет без _
  int totalCharsWithoutUnderscore = 0;
  for (const auto& countString : linesAfterVariant) {
    for (size_t i = 0; i < countString.length(); ++i) {
      if (countString[i] != '_') {
        totalCharsWithoutUnderscore++;
      }
    }
  }

  // Длины строк
  std::vector<int> stringLengths;
  for (const auto& lengthString : linesAfterVariant) {
    stringLengths.push_back(static_cast<int>(lengthString.length()));
  }

  std::ofstream outFile("output.txt");
  if (!outFile.is_open()) {
    std::cerr << "Error: Could not create output.txt" << std::endl;
    return;
  }

  outFile << "Original vector of strings\n";
  for (const auto& outputString : originalLines)
    outFile << outputString << "\n";

  outFile << "\nVector of strings after removing short lines\n";
  for (const auto& outputString : linesAfterRemoval)
    outFile << outputString << "\n";

  outFile << "\nVector of strings after replacing spaces with \"_\"\n";
  for (const auto& outputString : linesAfterVariant)
    outFile << outputString << "\n";

  outFile << "\nSearch result for the specified word\n" << searchResult << "\n";
  outFile << "\nTotal number of characters without \"_\"\n"
          << totalCharsWithoutUnderscore << "\n";

  outFile << "\nVector of string lengths\n";
  for (int currentLength : stringLengths) outFile << currentLength << " ";
  outFile << "\n";

  outFile.close();
}
