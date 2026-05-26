#pragma once

#include <string>

namespace homework {

// Runs the entire mini-homework 4 pipeline:
//   1. Generate a vector of 20 integers in [-50, 100] using std::generate
//      and std::mt19937.
//   2. Find min / max.
//   3. Sort ascending.
//   4. Count positive, negative and zero elements.
//   5. Compute the arithmetic mean.
//   6. Variant 1: remove all even numbers.
//   7. Sort the result and produce a vector of unique values.
// All intermediate results are written to the given output file.
//
// The implementation must not use any for / while loops.
void runHomework(const std::string& output_filename);

}  // namespace homework
