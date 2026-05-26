#include<iostream>
#include<vector>
#include<string>
#include<fstream>

int main() {
  std::vector<std::string> phrases;
  std::ifstream in("input.txt");
  if (in.is_open()) {
    std::string line;
    while (std::getline(in, line)) {
      phrases.push_back(line);
    }
  } else {
    std::cout << "NO INPUT FILE!!!1! SHAME ON YOU!";
    return 1;
  }
  in.close();

  std::vector<std::string> reserveCopy = phrases;
  
  int lineLength = 0;
  std::cout << "\nEnter the length of line: ";
  std::cin >> lineLength;
  while (lineLength < 1) {
    std::cout << "\nThe length is incorrect. Please enter a number greater "
                 "than or equal to 1: ";
    std::cin >> lineLength;
  }
  auto wrongLength = [lineLength](const std::string& line) {
    return line.length() < static_cast<size_t>(lineLength);
  };
  std::vector<std::string> withoutShort;
  for (auto& phrase : phrases) {
    if (!wrongLength(phrase)) withoutShort.push_back(phrase);
  }

  auto isWrongLetter = [](const char letter) { 
    return (letter == 'a' || letter == 'A' || letter == 'e' || letter == 'E' ||
            letter == 'i' || letter == 'I' || letter == 'o' || letter == 'O' ||
            letter == 'u' || letter == 'U' || letter == 'y' || letter == 'Y');
  };
  std::vector<std::string> deletedLetters = withoutShort;
  for (auto& phrase : deletedLetters) {
    std::string line;
    for (char& letter : phrase) {
      if (!isWrongLetter(letter)) line.push_back(letter);
    }
    phrase = line;
  }
  std::string word;
  std::cout << "\nType in the word to search: ";
  std::cin >> word;
  while (word.length() == 0) {
    std::cout << "\nYou need to type in a word: ";
    std::cin >> word;
  }
  auto hasWord = [&word](const std::string& phrase) { 
    return phrase.find(word) != std::string::npos;
  };
  std::string phraseWithWord = "Word not found";
  for (auto& phrase : phrases) {
    if (hasWord(phrase)) {
      phraseWithWord = phrase;
      break;
    }
  }

  auto countLetters = [](const std::string& phrase) {
    return static_cast<int>(phrase.length());
  };
  int wholeCount = 0;
  for (auto& phrase : deletedLetters) wholeCount += countLetters(phrase);

  std::vector<int> lineLengthes;
  for (auto& phrase : deletedLetters)
    lineLengthes.push_back(countLetters(phrase));

  std::ofstream out;
  out.open("output.txt");
  if (out.is_open()) {
    out << "\n1. The initial vector: ";
    for (auto& phrase : reserveCopy) out << phrase << "\n";
    out << "\n2. The vector with deleted short lines: ";
    for (auto& phrase : withoutShort) out << phrase << "\n";
    out << "\n3. The vector with deleted wrong letters: ";
    for (auto& phrase : deletedLetters) out << phrase << "\n";
    out << "\n4. The result of word search: " << phraseWithWord << "\n";
    out << "\n5. Word count: " << wholeCount << "\n";
    out << "\n6. The vector of lines lengthes: ";
    for (auto& phrase : lineLengthes) out << phrase << "\n";
  }
 }