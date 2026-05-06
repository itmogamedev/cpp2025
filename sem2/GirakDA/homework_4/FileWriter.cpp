#include "FileWriter.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include "VectorProcessor.h"

FileWriter::FileWriter(const std::string& file) : filename(file) {}

void FileWriter::process(const std::vector<int>& vec) {
  std::ofstream outFile(filename);

  outFile << "Original vector:" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(outFile, " "));
  outFile << std::endl << std::endl;

  auto stats = VectorProcessor::calculateStats(vec);
  outFile << "Minimum element: " << stats.min << std::endl;
  outFile << "Maximum element: " << stats.max << std::endl << std::endl;

  std::vector<int> sortedVec = vec;
  VectorProcessor::sortVector(sortedVec);
  outFile << "Sorted vector:" << std::endl;
  std::copy(sortedVec.begin(), sortedVec.end(),
            std::ostream_iterator<int>(outFile, " "));
  outFile << std::endl << std::endl;

  outFile << "Positive elements count: " << stats.positive << std::endl;
  outFile << "Negative elements count: " << stats.negative << std::endl;
  outFile << "Zero elements count: " << stats.zero << std::endl << std::endl;

  outFile << "Arithmetic mean: " << stats.average << std::endl << std::endl;

  std::vector<int> filteredVec = vec;
  VectorProcessor::removeEvenNumbers(filteredVec);
  outFile << "Vector after removing even numbers:" << std::endl;
  std::copy(filteredVec.begin(), filteredVec.end(),
            std::ostream_iterator<int>(outFile, " "));
  outFile << std::endl << std::endl;

  std::vector<int> uniqueVec = VectorProcessor::getUniqueSorted(filteredVec);
  outFile << "Vector with unique values:" << std::endl;
  std::copy(uniqueVec.begin(), uniqueVec.end(),
            std::ostream_iterator<int>(outFile, " "));
  outFile << std::endl;

  outFile.close();
}
