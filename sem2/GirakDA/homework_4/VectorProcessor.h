#pragma once

#include <vector>

class VectorProcessor {
 public:
  struct Stats {
    int min;
    int max;
    int positive;
    int negative;
    int zero;
    double average;
  };

  static Stats calculateStats(const std::vector<int>& vec);
  static void sortVector(std::vector<int>& vec);
  static void removeEvenNumbers(std::vector<int>& vec);
  static std::vector<int> getUniqueSorted(const std::vector<int>& vec);
};
