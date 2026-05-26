#ifndef VECTOR_PROCESSOR_H
#define VECTOR_PROCESSOR_H

#include <string>
#include <vector>

class VectorProcessor {
 public:
  explicit VectorProcessor(const std::string& output_file_name);

  void run();

 private:
  std::string output_file_name;

  std::vector<int> generateNumbers() const;
  int getMinValue(const std::vector<int>& numbers) const;
  int getMaxValue(const std::vector<int>& numbers) const;
  double getAverageValue(const std::vector<int>& numbers) const;
  int countPositiveNumbers(const std::vector<int>& numbers) const;
  int countNegativeNumbers(const std::vector<int>& numbers) const;
  int countZeroNumbers(const std::vector<int>& numbers) const;

  std::vector<int> sortNumbers(const std::vector<int>& numbers) const;
  std::vector<int> removeLessThanAverage(const std::vector<int>& numbers,
                                         double average_value) const;
  std::vector<int> getUniqueSortedNumbers(
      const std::vector<int>& numbers) const;

  void writeVector(std::ofstream& output_file,
                   const std::vector<int>& numbers) const;
};

#endif