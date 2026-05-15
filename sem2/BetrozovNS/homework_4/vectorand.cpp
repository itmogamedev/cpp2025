#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

// Writes a label and a vector of integers to the output stream.
void writeVector(std::ofstream& out, const std::string& label,
                 const std::vector<int>& vec) {
  out << label << "\n";
  std::for_each(vec.begin(), vec.end(), [&out](int val) { out << val << " "; });
  out << "\n\n";
}

int main() {
  std::ofstream output_file("output.txt");
  if (!output_file.is_open()) {
    std::cerr << "Error: cannot open output.txt\n";
    return 1;
  }

  // --- Step 1: Generate vector of 20 random integers in [-50, 100] ---
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::vector<int> numbers(20);
  std::generate(numbers.begin(), numbers.end(), [&]() { return dist(rng); });

  writeVector(output_file, "=== Generated vector ===", numbers);

  // --- Step 2: Find min and max elements ---
  auto min_it = std::min_element(numbers.begin(), numbers.end());
  auto max_it = std::max_element(numbers.begin(), numbers.end());

  output_file << "=== Min and Max ===\n";
  output_file << "Min: " << *min_it << "\n";
  output_file << "Max: " << *max_it << "\n\n";

  // --- Step 3: Sort ascending and write to file ---
  std::sort(numbers.begin(), numbers.end());
  writeVector(output_file, "=== Sorted vector ===", numbers);

  // --- Step 4: Count positive, negative and zero elements ---
  int positive_count = static_cast<int>(std::count_if(
      numbers.begin(), numbers.end(), [](int n) { return n > 0; }));
  int negative_count = static_cast<int>(std::count_if(
      numbers.begin(), numbers.end(), [](int n) { return n < 0; }));
  int zero_count = static_cast<int>(std::count_if(
      numbers.begin(), numbers.end(), [](int n) { return n == 0; }));

  output_file << "=== Element counts ===\n";
  output_file << "Positive: " << positive_count << "\n";
  output_file << "Negative: " << negative_count << "\n";
  output_file << "Zero:     " << zero_count << "\n\n";

  // --- Step 5: Calculate arithmetic mean ---
  double mean =
      static_cast<double>(std::accumulate(numbers.begin(), numbers.end(), 0)) /
      static_cast<double>(numbers.size());

  output_file << "=== Arithmetic mean ===\n";
  output_file << mean << "\n\n";

  // --- Step 6 (Variant 1): Remove all even numbers ---
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [](int n) { return n % 2 == 0; }),
                numbers.end());

  writeVector(output_file,
              "=== Vector after removing even numbers ===", numbers);

  // --- Step 7: Sort, then create vector of unique values ---
  std::sort(numbers.begin(), numbers.end());

  std::vector<int> unique_numbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_numbers));

  writeVector(output_file, "=== Unique values (sorted) ===", unique_numbers);

  std::cout << "Done. Results written to output.txt\n";
  return 0;
}
