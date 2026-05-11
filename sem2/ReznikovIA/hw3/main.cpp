#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void readAllData(std::vector<std::string>& vec, const std::string& fileName);
void workWithVector(std::vector<std::string>& vec);
void writeToFile(const std::vector<std::string>& data,
                 const std::string& outputFileName);
void writeToFile(const std::string& data, const std::string& outputFileName);
void clearFile(const std::string& fileName);

int main() {
  std::string inputFileLocation = "input.txt";
  std::vector<std::string> vec;
  readAllData(vec, inputFileLocation);
  workWithVector(vec);
  return 0;
}

void workWithVector(std::vector<std::string>& vec) {
  auto printVec = [&vec]() {
    std::cout << "[] printVec: " << std::endl;
    std::for_each(vec.cbegin(), vec.cend(),
                  [](const auto& line) { std::cout << line << std::endl; });
    std::cout << std::endl;
  };
  auto removeWordsLessThanInput = [&vec]() {
    std::cout << "[] removeWordsLessThanInput: " << std::endl;
    int minLength = 0;
    std::cout << "Input min word length (int): ";
    std::cin >> minLength;
    std::cout << "Entered number: " << minLength << std::endl;
    auto newEnd = std::remove_if(vec.begin(), vec.end(),
                                 [minLength](std::string& word) -> bool {
                                   return word.length() < minLength;
                                 });
    vec.erase(newEnd, vec.end());
    std::cout << std::endl;
  };
  auto changeSpacesToUnderscores = [&vec]() {
    std::cout << "[] changeSpacesToUnderscores: " << std::endl;
    std::for_each(vec.begin(), vec.end(), [](std::string& line) {
      std::replace(line.begin(), line.end(), ' ', '_');
    });
    std::cout << std::endl;
  };
  auto findInputWord = [&vec]() -> std::string {
    std::cout << "[] removeInputWord: " << std::endl;
    std::string word;
    std::cout << "Input word to find: ";
    std::cin >> word;
    std::cout << "Choosed word is: " << word << std::endl;
    auto it = std::find_if(vec.cbegin(), vec.cend(),
                           [&word](const std::string& line) {
                             return line.find(word) != std::string::npos;
                           });
    if (it != vec.cend()) {
      std::cout << "Found: " << *it << std::endl;
      std::cout << std::endl;
      return *it;
    } else {
      std::cout << "Not found!" << std::endl;
      std::cout << std::endl;
      return "Not found!";
    }
  };
  auto countCharsWithoutUnderscores = [&vec]() -> int {
    std::cout << "[] countCharsWithoutUnderscores: " << std::endl;
    int totalChars = 0;
    std::for_each(
        vec.begin(), vec.end(), [&totalChars](const std::string& line) {
          totalChars += std::count_if(line.cbegin(), line.cend(),
                                      [](char ch) { return ch != '_'; });
        });
    std::cout << "Total count: " << totalChars << std::endl;
    std::cout << std::endl;
    return totalChars;
  };
  auto createLinesLengthVector = [&vec]() -> std::vector<std::string> {
    std::cout << "[] createLinesLengthVector: " << std::endl;
    std::vector<std::string> lengthVec;
    std::for_each(vec.cbegin(), vec.cend(),
                  [&lengthVec](const std::string& line) {
                    lengthVec.push_back(std::to_string(line.length()));
                  });
    std::cout << "Vector created!" << std::endl;
    std::cout << std::endl;
    return lengthVec;
  };

  std::string outputFileName = "output.txt";

  clearFile(outputFileName);

  printVec();
  writeToFile(vec, outputFileName);
  writeToFile("---", outputFileName);

  removeWordsLessThanInput();
  printVec();
  writeToFile(vec, outputFileName);
  writeToFile("---", outputFileName);

  changeSpacesToUnderscores();
  printVec();
  writeToFile(vec, outputFileName);
  writeToFile("---", outputFileName);

  writeToFile(findInputWord(), outputFileName);
  writeToFile("---", outputFileName);

  writeToFile(std::to_string(countCharsWithoutUnderscores()), outputFileName);
  writeToFile("---", outputFileName);

  writeToFile(createLinesLengthVector(), outputFileName);
  writeToFile("---", outputFileName);
}

void writeToFile(const std::string& line, const std::string& fileName) {
  std::ofstream out(fileName, std::ios::app);
  if (out.is_open()) {
    out << line << std::endl;
  }
  out.close();
}

void writeToFile(const std::vector<std::string>& data,
                 const std::string& outputFileName) {
  std::for_each(data.cbegin(), data.cend(),
                [&data, &outputFileName](const std::string& line) {
                  writeToFile(line, outputFileName);
                });
}

void readAllData(std::vector<std::string>& vec, const std::string& fileName) {
  std::ifstream in(fileName);
  if (in.is_open()) {
    std::string line;
    while (std::getline(in, line)) {
      vec.push_back(line);
    }
  }
  in.close();
}

void clearFile(const std::string& fileName) {
  std::ofstream out(fileName);
  if (out.is_open()) {
  }
  out.close();
}
