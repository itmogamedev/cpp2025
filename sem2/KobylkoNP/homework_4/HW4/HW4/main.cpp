#include "random_generator.h"
#include "vector_processor.h"

int main() {
  auto vec = generate_random_vector();
  process_and_write_results(vec, "output.txt");
  return 0;
}
